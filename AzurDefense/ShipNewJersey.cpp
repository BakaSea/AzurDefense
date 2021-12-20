#include "ShipNewJersey.h"
#include "MissleHE.h"
#include "MissleAP.h"

ShipNewJersey::ShipNewJersey() {
	name = "NewJersey";
	size = vec2(2.0f, 2.0f);
	animateList.emplace_back(new Animation("Drag", 11, vec2(0.0f, -0.3f), vec2(1.0f / 0.8f, 1.0f / 0.8f)));
	animateList.emplace_back(new Animation("Stand", 16, vec2(0.0f, -0.1f), vec2(1.0f / 0.8f, 1.0f / 0.8f)));
	animateList.emplace_back(new Animation("Attack", 8, vec2(0.0f, -0.2f), vec2(1.0f / 0.8f, 1.0f / 0.8f)));
	animateList.emplace_back(new Animation("Dead", 22, vec2(0.2f, -0.3f), vec2(1.0f / 0.8f, 1.0f / 0.8f)));
	animateList.emplace_back(new Animation("Skill", 8, vec2(0.0f, -0.1f), vec2(1.0f / 0.8f, 1.0f / 0.8f), true));
	currentAnimation = animateList[0];
	armor = HEAVY;
	maxHp = 5000;
	atk = 2000;
	airDef = 300;
	energy = 20;
	maxBlock = 0;
	cooldown = 20.0f;
	attackFrame = 3;
	deadFrame = 21;
	attackRange = {
		vec2(-3.0f, 1.0f), vec2(-3.0f, 2.0f),
		vec2(-2.0f, 1.0f), vec2(-2.0f, 2.0f), vec2(-2.0f, 3.0f),
		vec2(-1.0f, 1.0f), vec2(-1.0f, 2.0f), vec2(-1.0f, 3.0f), vec2(-1.0f, 4.0f),
		vec2(0.0f, 1.0f), vec2(0.0f, 2.0f), vec2(0.0f, 3.0f), vec2(0.0f, 4.0f), vec2(0.0f, 5.0f),
		vec2(1.0f, 1.0f), vec2(1.0f, 2.0f), vec2(1.0f, 3.0f), vec2(1.0f, 4.0f),
		vec2(2.0f, 1.0f), vec2(2.0f, 2.0f), vec2(2.0f, 3.0f),
		vec2(3.0f, 1.0f), vec2(3.0f, 2.0f)
	};
	airDefRange = {
		vec2(-1.0f, -1.0f), vec2(-1.0f, 0.0f), vec2(-1.0f, 1.0f),
		vec2(0.0f, -1.0f), vec2(0.0f, 0.0f), vec2(0.0f, 1.0f),
		vec2(1.0f, -1.0f), vec2(1.0f, 0.0f), vec2(1.0f, 1.0f)
	};
	addChild(attackCD = new Timer(Timer::COUNTDOWN, 10000, false, Timer::FUNCNULL));
	addChild(airDefCD = new Timer(Timer::COUNTDOWN, 2000, false, Timer::FUNCNULL));
	addChild(skillCD = new Timer(Timer::COUNTDOWN, 20000, false, Timer::FUNCNULL));
}

GameObject* ShipNewJersey::createInstance() {
	return new ShipNewJersey();
}

string ShipNewJersey::getRarity() {
	return "UR";
}

bool ShipNewJersey::isLongDistance() {
	return true;
}

void ShipNewJersey::doAttack() {
	int index = rand() % enemyList.size();
	createThrowingObject(new MissleHE(), enemyList[index]->getPosition(), 0.3f,
		MathHelper::getFlyingTime(getPosition(), enemyList[index]->getPosition()), calculateDamage(nullptr) / 3.0f, 3, vec2(0.5f, 0.3f), vec2(2.0f, 2.0f));
}

void ShipNewJersey::doSkill() {
	if (hasEnemyInRange()) {
		int index = rand() % enemyList.size();
		createThrowingObject(new MissleAP(), enemyList[index]->getPosition(), 0.2f,
			MathHelper::getFlyingTime(getPosition(), enemyList[index]->getPosition()), calculateDamage(nullptr), 2, vec2(0.5f, 0.3f), vec2(2.0f, 2.0f));
	}
}
