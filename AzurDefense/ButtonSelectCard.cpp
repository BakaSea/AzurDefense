#include "ButtonSelectCard.h"
#include "Game.h"
#include "MathHelper.h"
#include "DebugHelper.h"
#include "Character.h"
#include "ScenePlay.h"

ButtonSelectCard::ButtonSelectCard(Ship* ship) {
	name = "ButtonSelectCard";
	size = vec2(1.5f, 1.5f);
	clickable = true;
	this->ship = ship;
	selected = false;
}

ButtonSelectCard::~ButtonSelectCard() {
	delete ship;
	ship = nullptr;
	selected = false;
}

int ButtonSelectCard::click(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			if (dynamic_cast<ContainerShip*>(parentObject)) {
				ScenePlay* scene = dynamic_cast<ScenePlay*>(Game::getInstance()->getSceneController()->getCurrentScene());
				if (scene != nullptr) {
					if (selected) {
						if (scene->removeBtnSelectCard(getShipName())) {
							selected = false;
						}
					} else {
						if (scene->addBtnSelectCard(getShipName())) {
							selected = true;
						}
					}
					return 2;
				}
			} else if (dynamic_cast<ScenePlay*>(parentObject)) {
				if (cdCount == 0.0f) {
					ScenePlay* scene = (ScenePlay*)parentObject;
					if (scene->isRunning()) {
						scene->decreaseEnergy(ship->getEnergy());
						cdCount = ship->getCooldown();

						double x, y;
						glfwGetCursorPos(window, &x, &y);
						MathHelper::Line ray = scene->getMainCamera()->screenToWorldLine((float)x, (float)y);
						MathHelper::Plane plane = MathHelper::Plane(0.0f, 1.0f, 0.0f, 0.0f);
						vec3 point = MathHelper::pointLinePlane(ray, plane);

						Character* instance = dynamic_cast<Character*>(ship->createInstance());
						Game::getInstance()->getSceneController()->getCurrentScene()->addObject(instance);
						instance->setPosition(point);
						instance->setStatus(Character::DRAG);
						instance->setRotation(Game::getInstance()->getSceneController()->getCurrentScene()->getMainCamera()->getPitch(), 0.0f, 0.0f);
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

void ButtonSelectCard::update() {
	GameObject::update();
	if (dynamic_cast<ScenePlay*>(parentObject)) {
		ScenePlay* scene = (ScenePlay*)parentObject;
		if (scene->isRunning()) {
			if (scene->getEnergy() < ship->getEnergy()) {
				clickable = false;
			} else {
				clickable = true;
			}
			if (cdCount > 0.0f) {
				cdCount -= (float)Game::getInstance()->getDeltaTime() / 1000.0f;
				if (cdCount <= 0.0f) {
					cdCount = 0.0f;
				}
			}
		}
	}
}

void ButtonSelectCard::render() {
	renderLowerChild();
	vec3 realPos = getPosition() + vec3(0.05f, -0.05f, 0.0f);
	vec2 realSize = getSize() - vec2(0.1f, 0.1f);
	Texture2D* background = Game::getInstance()->getResourceManager()->getTexture("UI/" + ship->getRarity()+ "BG");
	Game::getInstance()->getRenderer2D()->renderUI(background, realPos, getRotateZ(), realSize, getScaling(), vec2(0.0f, 0.0f), vec2(128.0f, 128.0f));
	Texture2D* texture = Game::getInstance()->getResourceManager()->getTexture(ship->getName() + "/" + ship->getName());
	Game::getInstance()->getRenderer2D()->renderUI(texture, realPos, getRotateZ(), realSize, getScaling(), vec2(0.0f, 0.0f), vec2(116.0f, 116.0f));
	Texture2D* frame = Game::getInstance()->getResourceManager()->getTexture("UI/" + ship->getRarity() + "Frame");
	Game::getInstance()->getRenderer2D()->renderUI(frame, realPos, getRotateZ(), realSize, getScaling(), vec2(0.0f, 0.0f), vec2(74.0f, 74.0f));
	if (selected || !canClick()) {
		Texture2D* black = Game::getInstance()->getResourceManager()->getTexture("UI/BlackAlpha");
		Game::getInstance()->getRenderer2D()->renderUI(black, realPos, getRotateZ(), realSize, getScaling(), vec2(0.0f, 0.0f), vec2(512.0f, 512.0f));
	}
	if (cdCount > 0.0f) {
		Texture2D* cd = Game::getInstance()->getResourceManager()->getTexture("UI/BlackAlpha");
		vec2 cdSize = realSize;
		cdSize.y *= cdCount / ship->getCooldown();
		Game::getInstance()->getRenderer2D()->renderUI(cd, realPos, getRotateZ(), cdSize, getScaling(), vec2(0.0f, 0.0f), vec2(512.0f, 512.0f));
	}
	renderUpperChild();
}

void ButtonSelectCard::clearCooldown() {
	cdCount = 0.0f;
}

string ButtonSelectCard::getShipName() {
	return ship->getName();
}
