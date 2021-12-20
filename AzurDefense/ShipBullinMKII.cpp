#include "ShipBullinMKII.h"
#include "Game.h"
#include "ScenePlay.h"
#include "ShipBullin.h"

ShipBullinMKII::ShipBullinMKII() {
	name = "BullinMKII";
	size = vec2(2.0f, 2.0f);
	animateList.emplace_back(new Animation("Drag", 5, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Stand", 19, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Attack", 8, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Dead", 7, vec2(0.3f, -0.5f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Skill", 8, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f), true));
	currentAnimation = animateList[0];
	armor = LIGHT;
	maxHp = 500;
	atk = 0;
	energy = 10;
	maxBlock = 10;
	cooldown = 10.0f;
	attackFrame = 4;
	deadFrame = 6;
	attackRange.emplace_back(vec2(-1.0f, 1.0f));
	attackRange.emplace_back(vec2(0.0f, 1.0f));
	attackRange.emplace_back(vec2(1.0f, 1.0f));
	addChild(attackCD = new Timer(Timer::COUNTDOWN, 5000, false, Timer::FUNCNULL));
	addChild(airDefCD = new Timer(Timer::COUNTDOWN, 0, false, Timer::FUNCNULL));
	addChild(skillCD = new Timer(Timer::COUNTDOWN, 20000, false, Timer::FUNCNULL));
}

GameObject* ShipBullinMKII::createInstance() {
	return new ShipBullinMKII();
}

string ShipBullinMKII::getRarity() {
	return "SSR";
}

bool ShipBullinMKII::isLongDistance() {
	return true;
}

bool ShipBullinMKII::hasEnemyInRange() {
	placeLocList.clear();
	ScenePlay* scene = dynamic_cast<ScenePlay*>(Game::getInstance()->getSceneController()->getCurrentScene());
	if (scene != nullptr) {
		for (vec2& range : attackRange) {
			mat4 model = MathHelper::getModelMatrix(vec3(0.0f), 0.0f, 0.0f, orientDegree, vec2(1.0f, 1.0f), vec2(1.0f, 1.0f));
			vec4 point(range, 0.0f, 0.0f);
			point = model * point;
			vec2 loc(point);
			loc += getLocation();
			GameMap::TYPE type = scene->getGameMap()->getPlatformType(loc);
			if (type == GameMap::NORMAL || type == GameMap::SHORT) {
				Ship* ship = scene->getShip(loc);
				if (ship == nullptr) {
					placeLocList.emplace_back(loc);
				}
			}
		}
	}
	return !placeLocList.empty();
}

void ShipBullinMKII::doAttack() {
	ScenePlay* scene = dynamic_cast<ScenePlay*>(Game::getInstance()->getSceneController()->getCurrentScene());
	if (scene != nullptr) {
		for (vec2 loc : placeLocList) {
			ShipBullin* bullin = new ShipBullin();
			bullin->setLayer(ScenePlay::CHARACTER);
			bullin->setOrient(orientation);
			bullin->setRotation(scene->getMainCamera()->getPitch(), 0.0f, 0.0f);
			scene->addObject(bullin);
			scene->addCharacter(loc, bullin);
		}
	}
}

void ShipBullinMKII::doSkill() {

}
