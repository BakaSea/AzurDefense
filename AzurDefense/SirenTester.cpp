#include "SirenTester.h"
#include "MissleAP.h"
#include "MissleHE.h"
#include "MissleNormal.h"

SirenTester::SirenTester() {
	name = "Tester";
	size = vec2(2.0f, 2.0f);
	animateList.emplace_back(new Animation("Move", 37, vec2(0.0f, -0.3f), vec2(1.0f / 0.4f, 1.0f / 0.4f)));
	animateList.emplace_back(new Animation("Attack", 8, vec2(0.0f, -0.3f), vec2(1.0f / 0.4f, 1.0f / 0.4f)));
	animateList.emplace_back(new Animation("Dead", 5, vec2(0.0f, -0.8f), vec2(1.0f / 0.4f, 1.0f / 0.4f)));
	currentAnimation = animateList[0];
	armor = HEAVY;
	maxHp = 30000;
	atk = 450;
	airDef = 400;
	attackFrame = 4;
	deadFrame = 4;
	attackRange = {
		vec2(-3.0f, 1.0f), vec2(-3.0f, 2.0f),
		vec2(-2.0f, 1.0f), vec2(-2.0f, 2.0f), vec2(-2.0f, 3.0f),
		vec2(-1.0f, 1.0f), vec2(-1.0f, 2.0f), vec2(-1.0f, 3.0f), vec2(-1.0f, 4.0f),
		vec2(0.0f, 1.0f), vec2(0.0f, 2.0f), vec2(0.0f, 3.0f), vec2(0.0f, 4.0f), vec2(0.0f, 5.0f), vec2(0.0f, 6.0f),
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
	addChild(skillCD = new Timer(Timer::COUNTDOWN, 3000, false, Timer::FUNCNULL));
	velocity = 0.1f;
	energy = 100;
	skillTimes = false;
}

GameObject* SirenTester::createInstance() {
	return new SirenTester();
}

bool SirenTester::isBoss() {
	return true;
}

void SirenTester::doAttack() {
	for (Character* enemy : enemyList) {
		createThrowingObject(new MissleAP(), enemy->getPosition(), 1.0f, MathHelper::getFlyingTime(getPosition(), enemy->getPosition()),
			calculateDamage(nullptr), 1, vec2(0.5f, 0.3f), vec2(2.0f, 2.0f));
	}
}

void SirenTester::doSkill() {
	MissleNormal* missle;
	if (skillTimes) {
		missle = new MissleNormal();
	} else {
		missle = new MissleHE();
	}
	createThrowingObject(missle, 15.0f, 3.0f, calculateDamage(nullptr) / 10.0f, 10, vec2(0.5f, 0.3f), vec2(1.0f, 1.0f));
	skillTimes ^= 1;
}
