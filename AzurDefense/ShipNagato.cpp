#include "ShipNagato.h"
#include "MissleNormal.h"

ShipNagato::ShipNagato() {
	name = "Nagato";
	size = vec2(2.0f, 2.0f);
	animateList.emplace_back(new Animation("Drag", 4, vec2(0.0f, -0.3f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Stand", 20, vec2(0.0f, -0.2f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Attack", 8, vec2(0.0f, -0.2f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Dead", 8, vec2(0.4f, -0.5f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Skill", 8, vec2(0.0f, -0.2f), vec2(1.0f , 1.0f), true));
	currentAnimation = animateList[0];
	armor = HEAVY;
	maxHp = 4000;
	atk = 1500;
	airDef = 250;
	energy = 10;
	maxBlock = 0;
	cooldown = 10.0f;
	attackFrame = 4;
	deadFrame = 7;
	attackRange = {
		vec2(-2.0f, 1.0f),
		vec2(-1.0f, 1.0f), vec2(-1.0f, 2.0f), vec2(-1.0f, 3.0f),
		vec2(0.0f, 1.0f), vec2(0.0f, 2.0f), vec2(0.0f, 3.0f), vec2(0.0f, 4.0f), vec2(0.0f, 5.0f),
		vec2(1.0f, 1.0f), vec2(1.0f, 2.0f), vec2(1.0f, 3.0f),
		vec2(2.0f, 1.0f)
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

GameObject* ShipNagato::createInstance() {
	return new ShipNagato();
}

string ShipNagato::getRarity() {
	return "SSR";
}

bool ShipNagato::isLongDistance() {
	return true;
}

void ShipNagato::doAttack() {
	int index = rand() % enemyList.size();
	createThrowingObject(new MissleNormal(), enemyList[index]->getPosition(), 0.4f,
		MathHelper::getFlyingTime(getPosition(), enemyList[index]->getPosition()), calculateDamage(nullptr) / 4.0f, 4, vec2(0.5f, 0.3f), vec2(2.0f, 2.0f));
}

void ShipNagato::doSkill() {
	createThrowingObject(new MissleNormal(), 10.0f, 3.0f, calculateDamage(nullptr) / 7.0f, 7, vec2(0.5f, 0.3f), vec2(2.0f, 2.0f));
}
