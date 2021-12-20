#include "SirenZero.h"
#include "MissleNormal.h"
#include "MissleHE.h"
#include "Torpedo.h"
#include "ACBomber.h"

SirenZero::SirenZero() {
	name = "Zero";
	size = vec2(2.0f, 2.0f);
	animateList.emplace_back(new Animation("Move", 24, vec2(0.0f, -0.3f), vec2(1.0f / 0.5f, 1.0f / 0.5f)));
	animateList.emplace_back(new Animation("Attack", 8, vec2(0.0f, -0.3f), vec2(1.0f / 0.5f, 1.0f / 0.5f)));
	animateList.emplace_back(new Animation("Dead", 9, vec2(0.0f, -0.8f), vec2(1.0f / 0.5f, 1.0f / 0.5f)));
	currentAnimation = animateList[0];
	armor = MIDDIUM;
	maxHp = 50000;
	atk = 500;
	airDef = 200;
	attackFrame = 3;
	deadFrame = 8;
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
	addChild(attackCD = new Timer(Timer::COUNTDOWN, 2000, false, Timer::FUNCNULL));
	addChild(airDefCD = new Timer(Timer::COUNTDOWN, 2000, false, Timer::FUNCNULL));
	addChild(skillCD = new Timer(Timer::COUNTDOWN, 5000, false, Timer::FUNCNULL));
	velocity = 0.1f;
	energy = 100;
	skillTime = 0;
}

GameObject* SirenZero::createInstance() {
	return new SirenZero();
}

bool SirenZero::isBoss() {
	return true;
}

void SirenZero::doAttack() {
	int index = rand() % enemyList.size();
	createThrowingObject(new MissleNormal(), enemyList[index]->getPosition(), 0.5f, MathHelper::getFlyingTime(getPosition(), enemyList[index]->getPosition()),
		calculateDamage(nullptr) / 2.0f, 2, vec2(0.5f, 0.3f), vec2(2.0f, 2.0f));
}

void SirenZero::doSkill() {
	switch (skillTime) {
	case 0: {
		createThrowingObject(new Torpedo(), 15.0f, 3.0f, calculateDamage(nullptr) / 5.0f, 5, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f));
		break;
	}
	case 1: {
		createThrowingObject(new MissleHE(), 20.0f, 3.0f, calculateDamage(nullptr) / 5.0f, 5, vec2(0.5f, 0.3f), vec2(1.5f, 1.5f));
		break;
	}
	case 2: {
		createAircraft(new ACBomber(), getAttack() / 3, 0, getMaxHp() / 100, true, vec2(1.0f, 0.0f), 0);
		createAircraft(new ACBomber(), getAttack() / 3, 0, getMaxHp() / 100, true, vec2(0.0f, 0.0f), 0);
		createAircraft(new ACBomber(), getAttack() / 3, 0, getMaxHp() / 100, true, vec2(-1.0f, 0.0f), 0);
		break;
	}
	}
	skillTime = (skillTime + 1) % 3;
}
