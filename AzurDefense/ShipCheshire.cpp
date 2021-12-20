#include "ShipCheshire.h"
#include "MissleHE.h"
#include "BuffAirDefImpRate.h"
#include "BuffAtkImpRate.h"

ShipCheshire::ShipCheshire() {
	name = "Cheshire";
	size = vec2(2.0f, 2.0f);
	animateList.emplace_back(new Animation("Drag", 11, vec2(0.0f, -0.1f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Stand", 24, vec2(0.0f, -0.1f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Attack", 8, vec2(0.0f, -0.1f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Dead", 8, vec2(0.2f, -0.4f), vec2(1.0f / 0.9f, 1.0f / 0.9f)));
	animateList.emplace_back(new Animation("Skill", 8, vec2(0.0f, -0.1f), vec2(1.0f, 1.0f), true));
	currentAnimation = animateList[0];
	armor = MIDDIUM;
	maxHp = 2000;
	atk = 500;
	airDef = 500;
	energy = 10;
	maxBlock = 0;
	cooldown = 10.0f;
	attackFrame = 3;
	deadFrame = 7;
	attackRange = {
		vec2(0.0f, 1.0f), vec2(0.0f, 2.0f), vec2(0.0f, 3.0f), vec2(0.0f, 4.0f), vec2(0.0f, 5.0f), vec2(0.0f, 6.0f)
	};
	airDefRange = {
		vec2(-2.0f, -2.0f), vec2(-2.0f, -1.0f), vec2(-2.0f, 0.0f), vec2(-2.0f, 1.0f), vec2(-2.0f, 2.0f),
		vec2(-1.0f, -2.0f), vec2(-1.0f, -1.0f), vec2(-1.0f, 0.0f), vec2(-1.0f, 1.0f), vec2(-1.0f, 2.0f),
		vec2(0.0f, -2.0f), vec2(0.0f, -1.0f), vec2(0.0f, 0.0f), vec2(0.0f, 1.0f), vec2(0.0f, 2.0f),
		vec2(1.0f, -2.0f), vec2(1.0f, -1.0f), vec2(1.0f, 0.0f), vec2(1.0f, 1.0f), vec2(1.0f, 2.0f),
		vec2(2.0f, -2.0f), vec2(2.0f, -1.0f), vec2(2.0f, 0.0f), vec2(2.0f, 1.0f), vec2(2.0f, 2.0f)
	};
	addChild(attackCD = new Timer(Timer::COUNTDOWN, 3000, false, Timer::FUNCNULL));
	addChild(airDefCD = new Timer(Timer::COUNTDOWN, 1500, false, Timer::FUNCNULL));
	addChild(skillCD = new Timer(Timer::COUNTDOWN, 20000, false, Timer::FUNCNULL));
}

GameObject* ShipCheshire::createInstance() {
	return new ShipCheshire();
}

bool ShipCheshire::isLongDistance() {
	return true;
}

string ShipCheshire::getRarity() {
	return "SSR";
}

void ShipCheshire::doAttack() {
	createThrowingObject(new MissleHE(), 5.0f, 3.0f, calculateDamage(nullptr) / 3, 3, vec2(0.5f, 0.3f), vec2(1.5f, 1.5f));
}

void ShipCheshire::doSkill() {
	addChild(new BuffAirDefImpRate(0.5f, 5000));
	addChild(new BuffAtkImpRate(0.15f, 5000));
}
