#include "SirenPurifier.h"
#include "MissleHE.h"
#include "Torpedo.h"

SirenPurifier::SirenPurifier() {
	name = "Purifier";
	size = vec2(2.0f, 2.0f);
	animateList.emplace_back(new Animation("Move", 23, vec2(0.0f, -0.3f), vec2(1.0f / 0.5f, 1.0f / 0.5f)));
	animateList.emplace_back(new Animation("Attack", 8, vec2(0.0f, -0.3f), vec2(1.0f / 0.5f, 1.0f / 0.5f)));
	animateList.emplace_back(new Animation("Dead", 6, vec2(0.0f, -0.8f), vec2(1.0f / 0.5f, 1.0f / 0.5f)));
	currentAnimation = animateList[0];
	armor = MIDDIUM;
	maxHp = 20000;
	atk = 400;
	airDef = 300;
	attackFrame = 3;
	deadFrame = 5;
	attackRange = {
		vec2(-2.0f, 1.0f), vec2(-2.0f, 2.0f),
		vec2(-1.0f, 1.0f), vec2(-1.0f, 2.0f), vec2(-1.0f, 3.0f), vec2(-1.0f, 4.0f),
		vec2(0.0f, 1.0f), vec2(0.0f, 2.0f), vec2(0.0f, 3.0f), vec2(0.0f, 4.0f), vec2(0.0f, 5.0f), vec2(0.0f, 6.0f),
		vec2(1.0f, 1.0f), vec2(1.0f, 2.0f), vec2(1.0f, 3.0f), vec2(1.0f, 4.0f),
		vec2(2.0f, 1.0f), vec2(2.0f, 2.0f)
	};
	airDefRange = {
		vec2(-1.0f, -1.0f), vec2(-1.0f, 0.0f), vec2(-1.0f, 1.0f),
		vec2(0.0f, -1.0f), vec2(0.0f, 0.0f), vec2(0.0f, 1.0f),
		vec2(1.0f, -1.0f), vec2(1.0f, 0.0f), vec2(1.0f, 1.0f)
	};
	addChild(attackCD = new Timer(Timer::COUNTDOWN, 10000, false, Timer::FUNCNULL));
	addChild(airDefCD = new Timer(Timer::COUNTDOWN, 2000, false, Timer::FUNCNULL));
	addChild(skillCD = new Timer(Timer::COUNTDOWN, 5000, false, Timer::FUNCNULL));
	velocity = 0.1f;
	energy = 100;
}

GameObject* SirenPurifier::createInstance() {
	return new SirenPurifier();
}

bool SirenPurifier::isBoss() {
	return true;
}

void SirenPurifier::doAttack() {
	int index = rand() % enemyList.size();
	createThrowingObject(new MissleHE(), enemyList[index]->getPosition(), 1.0f, MathHelper::getFlyingTime(getPosition(), enemyList[index]->getPosition()),
		calculateDamage(nullptr) / 2.0f, 2, vec2(0.5f, 0.3f), vec2(2.0f, 2.0f));
}

void SirenPurifier::doSkill() {
	createThrowingObject(new Torpedo(), 15.0f, 2.0f, calculateDamage(nullptr) / 10.0f, 5, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f));
}
