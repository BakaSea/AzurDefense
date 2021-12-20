#include "ShipLaffey.h"
#include "MissleNormal.h"
#include "BuffAtkImpRate.h"
#include "BuffAirDefImpRate.h"

ShipLaffey::ShipLaffey() {
	name = "Laffey";
	size = vec2(2.0f, 2.0f);
	animateList.emplace_back(new Animation("Drag", 4, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Stand", 19, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Attack", 8, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Dead", 6, vec2(0.3f, -0.5f), vec2(1.0f / 0.7f, 1.0f / 0.7f)));
	animateList.emplace_back(new Animation("Skill", 8, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f), true));
	currentAnimation = animateList[0];
	armor = LIGHT;
	maxHp = 800;
	atk = 100;
	airDef = 200;
	energy = 5;
	maxBlock = 0;
	cooldown = 5.0f;
	attackFrame = 6;
	deadFrame = 5;
	attackRange.emplace_back(vec2(0.0f, 1.0f));
	attackRange.emplace_back(vec2(0.0f, 2.0f));
	attackRange.emplace_back(vec2(0.0f, 3.0f));
	attackRange.emplace_back(vec2(0.0f, 4.0f));
	airDefRange.emplace_back(vec2(-1.0f, -1.0f));
	airDefRange.emplace_back(vec2(-1.0f, 0.0f));
	airDefRange.emplace_back(vec2(-1.0f, 1.0f));
	airDefRange.emplace_back(vec2(0.0f, -1.0f));
	airDefRange.emplace_back(vec2(0.0f, 0.0f));
	airDefRange.emplace_back(vec2(0.0f, 1.0f));
	airDefRange.emplace_back(vec2(1.0f, -1.0f));
	airDefRange.emplace_back(vec2(1.0f, 0.0f));
	airDefRange.emplace_back(vec2(1.0f, 1.0f));
	addChild(attackCD = new Timer(Timer::COUNTDOWN, 0, false, Timer::FUNCNULL));
	addChild(airDefCD = new Timer(Timer::COUNTDOWN, 2000, false, Timer::FUNCNULL));
	addChild(skillCD = new Timer(Timer::COUNTDOWN, 20000, false, Timer::FUNCNULL));
}

GameObject* ShipLaffey::createInstance() {
	return new ShipLaffey();
}

string ShipLaffey::getRarity() {
	return "SR";
}

bool ShipLaffey::isLongDistance() {
	return true;
}

void ShipLaffey::doAttack() {
	createThrowingObject(new MissleNormal(), 0.0f, 3.0f, calculateDamage(nullptr), 1, vec2(0.5f, 0.3f), vec2(1.0f, 1.0f));
}

void ShipLaffey::doSkill() {
	addChild(new BuffAtkImpRate(0.2f, 8000));
	addChild(new BuffAirDefImpRate(0.4f, 8000));
}
