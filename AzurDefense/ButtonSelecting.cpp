#include "ButtonSelecting.h"
#include "Game.h"
#include "ScenePlay.h"
#include "DebugHelper.h"

ButtonSelecting::ButtonSelecting() {
	name = "ButtonSelecting";
	size = vec2(3.0f, 3.0f);
	clickable = true;
}

void ButtonSelecting::start() {
	startChild();
	Character* charac = dynamic_cast<Character*>(parentObject);
	setOrient(charac->getOrient());
}

void ButtonSelecting::render() {
	renderLowerChild();
	Texture2D* texture = Game::getInstance()->getResourceManager()->getTexture("UI/Selecting");
	Game::getInstance()->getRenderer2D()->renderUI3D(texture, getPosition(), size, getRotateX(), getRotateY(), getRotateZ(), getScaling(), vec2(0.0f, 0.0f), vec2(600.0f, 600.0f));
	vec3 offset(0.0f);
	switch (orientation) {
	case Character::RIGHT: {
		offset.x = 2.0f;
		offset.z = 1.0f;
		break;
	}
	case Character::DOWN: {
		offset.x = 1.0f;
		offset.z = 2.0f;
		break;
	}
	case Character::LEFT: {
		offset.x = 0.0f;
		offset.z = 1.0f;
		break;
	}
	case Character::UP: {
		offset.x = 1.0f;
		offset.z = 0.0f;
		break;
	}
	}
	Game::getInstance()->getRenderer2D()->renderUI3D(texture, getPosition() + offset, vec2(1.0f, 1.0f), getRotateX(), getRotateY(), getRotateZ(),
		getScaling(), vec2(600.0f, orientation * 200.0f), vec2(200.0f, 200.0f));


	Ship* charac = dynamic_cast<Ship*>(parentObject);

	Texture2D* skill = Game::getInstance()->getResourceManager()->getTexture(charac->getName() + "/SkillIcon");
	Game::getInstance()->getRenderer2D()->renderUI3D(skill, getPosition(), vec2(1.0f, 1.0f), getRotateX(), getRotateY(), getRotateZ(), getScaling(),
		vec2(0.0f, 0.0f), vec2(64.0f, 64.0f));
	Timer* skillCD = charac->getSkillCD();
	if (!skillCD->timeOut()) {
		Texture2D* black = Game::getInstance()->getResourceManager()->getTexture("UI/BlackAlpha");
		vec2 blackSize = vec2(1.0f, 1.0f);
		blackSize.y *= 1.0f - (float)skillCD->getTimeCount() / (float)skillCD->getTiming();
		Game::getInstance()->getRenderer2D()->renderUI3D(black, getPosition(), blackSize, getRotateX(), getRotateY(), getRotateZ(), getScaling(),
			vec2(0.0f, 0.0f), vec2(512.0f, 512.0f));
	}

	Texture2D* textureRange = Game::getInstance()->getResourceManager()->getTexture("UI/AttackRange");
	vector<vec2> attackRange = charac->getAttackRange();
	ScenePlay* scene = dynamic_cast<ScenePlay*>(Game::getInstance()->getSceneController()->getCurrentScene());
	for (vec2& range : attackRange) {
		mat4 model = MathHelper::getModelMatrix(vec3(0.0f), 0.0f, 0.0f, orientDegree, vec2(1.0f, 1.0f), vec2(1.0f, 1.0f));
		vec4 point(range, 0.0f, 0.0f);
		point = model * point;
		vec3 rangePos = scene->getPositionByLocation(charac->getLocation() + vec2(point));
		if (rangePos != vec3(-1.0f, -1.0f, -1.0f)) {
			Game::getInstance()->getRenderer2D()->render(textureRange, rangePos, vec2(1.0f, 1.0f), getRotateX(), getRotateY(), getRotateZ(),
						getScaling(), Renderer2D::MIDDLE);
		}
	}
	Texture2D* textureAirRange = Game::getInstance()->getResourceManager()->getTexture("UI/AirRange");
	vector<vec2> airDefRange = charac->getAirDefRange();
	for (vec2& range : airDefRange) {
		mat4 model = MathHelper::getModelMatrix(vec3(0.0f), 0.0f, 0.0f, orientDegree, vec2(1.0f, 1.0f), vec2(1.0f, 1.0f));
		vec4 point(range, 0.0f, 0.0f);
		point = model * point;
		vec3 rangePos = scene->getPositionByLocation(charac->getLocation() + vec2(point));
		if (rangePos != vec3(-1.0f, -1.0f, -1.0f)) {
			Game::getInstance()->getRenderer2D()->render(textureAirRange, rangePos, vec2(1.0f, 1.0f), getRotateX(), getRotateY(), getRotateZ(),
				getScaling(), Renderer2D::MIDDLE);
		}
	}
	renderUpperChild();
}

int ButtonSelecting::click(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			MathHelper::Line ray = Game::getInstance()->getSceneController()->getCurrentScene()->getMainCamera()->screenToWorldLine((float)x, (float)y);
			vec3 point = MathHelper::pointLinePlane(ray, getPlane());
			vec4 p(point, 1.0f);
			p = inverse(MathHelper::getModelMatrix(getPosition(), getRotateX(), getRotateY(), getRotateZ(), getScaling(), vec2(1.0f, 1.0f))) * p;
			if (2.0f <= p.x && p.x <= 3.0f && -2.0f <= p.y && p.y <= -1.0f) {
				setOrient(Character::RIGHT);
				return 1;
			} else if (1.0f <= p.x && p.x <= 2.0f && -3.0f <= p.y && p.y <= -2.0f) {
				setOrient(Character::DOWN);
				return 1;
			} else if (0.0f <= p.x && p.x <= 1.0f && -2.0f <= p.y && p.y <= -1.0f) {
				setOrient(Character::LEFT);
				return 1;
			} else if (1.0f <= p.x && p.x <= 2.0f && -1.0f <= p.y && p.y <= 0.0f) {
				setOrient(Character::UP);
				return 1;
			} else if (2.0f <= p.x && p.x <= 3.0f && -1.0f <= p.y && p.y <= 0.0f) {
				ScenePlay* scene = dynamic_cast<ScenePlay*>(Game::getInstance()->getSceneController()->getCurrentScene());
				Character* charac = dynamic_cast<Character*>(parentObject);
				scene->increaseEnergy((int)((float)charac->getHp() / (float)charac->getMaxHp() * (float)charac->getEnergy()));
				scene->removeCharacter(charac->getLocation(), charac);
				return 3;
			} else if (2.0f <= p.x && p.x <= 3.0f && -3.0f <= p.y && p.y <= -2.0f) {
				Character* charac = dynamic_cast<Character*>(parentObject);
				charac->setOrient(orientation);
				remove();
				return 2;
			} else if (0.0f <= p.x && p.x <= 1.0f && -1.0f <= p.y && p.y <= 0.0f) {
				Character* ship = dynamic_cast<Character*>(parentObject);
				if (ship->getSkillCD()->timeOut()) {
					ship->useSkill();
					remove();
				}
				return 5;
			} else {
				return 4;
			}
		}
	}
	return 0;
}

bool ButtonSelecting::is3D() {
	return true;
}

void ButtonSelecting::setOrient(Character::ORIENT orient) {
	orientation = orient;
	switch (orient) {
	case Character::RIGHT: {
		orientDegree = 0.0f;
		break;
	}
	case Character::DOWN: {
		orientDegree = -90.0f;
		break;
	}
	case Character::LEFT: {
		orientDegree = 180.0f;
		break;
	}
	case Character::UP: {
		orientDegree = 90.0f;
		break;
	}
	}
}
