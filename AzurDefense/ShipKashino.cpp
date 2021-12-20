#include "ShipKashino.h"
#include "BuffHeal.h"

ShipKashino::ShipKashino() {
	name = "Kashino";
	size = vec2(2.0f, 2.0f);
	animateList.emplace_back(new Animation("Drag", 8, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Stand", 19, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Attack", 9, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Dead", 8, vec2(0.3f, -0.5f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Skill", 9, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f), true));
	currentAnimation = animateList[0];
	armor = LIGHT;
	maxHp = 5000;
	atk = 0;
	energy = 5;
	maxBlock = 10;
	cooldown = 5.0f;
	deadFrame = 7;
	attackRange.emplace_back(vec2(0.0f, 0.0f));
	attackRange.emplace_back(vec2(0.0f, 1.0f));
	addChild(attackCD = new Timer(Timer::COUNTDOWN, 0, false, Timer::FUNCNULL));
	addChild(airDefCD = new Timer(Timer::COUNTDOWN, 0, false, Timer::FUNCNULL));
	addChild(skillCD = new Timer(Timer::COUNTDOWN, 20000, false, Timer::FUNCNULL));
}

GameObject* ShipKashino::createInstance() {
	return new ShipKashino();
}

string ShipKashino::getRarity() {
	return "SR";
}

void ShipKashino::doSkill() {
	addChild(new BuffHeal((float)maxHp * 0.2f));
}
