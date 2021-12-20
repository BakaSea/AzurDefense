#include "ButtonFormation.h"
#include "Game.h"
#include "ScenePlay.h"

ButtonFormation::ButtonFormation() {
	name = "ButtonFormation";
	size = vec2(2.658f, 1.0f);
	clickable = true;
	container = nullptr;
}

void ButtonFormation::render() {
	renderLowerChild();
	Texture2D* texture = Game::getInstance()->getResourceManager()->getTexture("UI/ButtonFormation");
	Game::getInstance()->getRenderer2D()->renderUI(texture, getPosition(), getRotateZ(), getSize(), getScaling(), vec2(0.0f, 0.0f), vec2(428.0f, 161.0f));
	renderUpperChild();
}

int ButtonFormation::click(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			if (container == nullptr) {
				addChild(container = new ContainerShip());
				container->enableAbsolutePosition();
				container->setPosition(-6.5f, 4.5f);
			} else {
				removeChild(container);
				container = nullptr;
			}
		}
	}
	return 0;
}
