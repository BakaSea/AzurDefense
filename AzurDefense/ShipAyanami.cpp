#include "ShipAyanami.h"
#include "Torpedo.h"

ShipAyanami::ShipAyanami() {
	name = "Ayanami";
	size = vec2(2.0f, 2.0f);
	animateList.emplace_back(new Animation("Drag", 8, vec2(0.0f, -0.3f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Stand", 8, vec2(0.0f, -0.1f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Attack", 8, vec2(0.0f, -0.1f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Dead", 7, vec2(0.2f, -0.5f), vec2(1.0f / 0.7f, 1.0f / 0.7f)));
	animateList.emplace_back(new Animation("Skill", 8, vec2(0.0f, -0.7f), vec2(1.0f / 0.9f, 1.0f / 0.9f), true));
	currentAnimation = animateList[0];
	armor = LIGHT;
	maxHp = 1000;
	atk = 250;
	energy = 5;
	maxBlock = 2;
	cooldown = 5.0f;
	attackFrame = 4;
	deadFrame = 6;
	attackRange.emplace_back(vec2(0.0f, 0.0f));
	attackRange.emplace_back(vec2(0.0f, 1.0f));
	addChild(attackCD = new Timer(Timer::COUNTDOWN, 0, false, Timer::FUNCNULL));
	addChild(airDefCD = new Timer(Timer::COUNTDOWN, 0, false, Timer::FUNCNULL));
	addChild(skillCD = new Timer(Timer::COUNTDOWN, 20000, false, Timer::FUNCNULL));
}

GameObject* ShipAyanami::createInstance() {
	return new ShipAyanami();
}

string ShipAyanami::getRarity() {
	return "SR";
}

void ShipAyanami::doSkill() {
	createThrowingObject(new Torpedo(), 5.0f, 3.0f, calculateDamage(nullptr), 3, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f));
}
