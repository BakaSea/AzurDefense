#include "ShipZ23.h"
#include "MissleNormal.h"
#include "Game.h"
#include "ScenePlay.h"
#include "DebugHelper.h"
#include "BuffAtkImpRate.h"

ShipZ23::ShipZ23() {
	name = "Z23";
	size = vec2(2.0f, 2.0f);
	animateList.emplace_back(new Animation("Drag", 11, vec2(0.0f, -0.1f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Stand", 19, vec2(0.0f, -0.1f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Attack", 8, vec2(0.0f, -0.1f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Dead", 7, vec2(0.3f, -0.5f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Skill", 8, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f), true));
	currentAnimation = animateList[0];
	armor = LIGHT;
	maxHp = 800;
	atk = 120;
	energy = 5;
	maxBlock = 0;
	cooldown = 5.0f;
	attackFrame = 6;
	deadFrame = 6;
	attackRange.emplace_back(vec2(0.0f, 1.0f));
	attackRange.emplace_back(vec2(0.0f, 2.0f));
	attackRange.emplace_back(vec2(0.0f, 3.0f));
	attackRange.emplace_back(vec2(0.0f, 4.0f));
	addChild(attackCD = new Timer(Timer::COUNTDOWN, 0, false, Timer::FUNCNULL));
	addChild(airDefCD = new Timer(Timer::COUNTDOWN, 0, false, Timer::FUNCNULL));
	addChild(skillCD = new Timer(Timer::COUNTDOWN, 20000, false, Timer::FUNCNULL));
}

GameObject* ShipZ23::createInstance() {
	return new ShipZ23();
}

string ShipZ23::getRarity() {
	return "SR";
}

bool ShipZ23::isLongDistance() {
	return true;
}

void ShipZ23::doAttack() {
	createThrowingObject(new MissleNormal(), 5.0f, 3.0f, calculateDamage(nullptr) / 2.0f, 2, vec2(0.5f, 0.3f), vec2(1.0f, 1.0f));
}

void ShipZ23::doSkill() {
	addChild(new BuffAtkImpRate(0.6f, 8000));
}
