#include "ShipBullin.h"

ShipBullin::ShipBullin() {
	name = "Bullin";
	size = vec2(2.0f, 2.0f);
	animateList.emplace_back(new Animation("Drag", 8, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Stand", 19, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Attack", 8, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Dead", 7, vec2(0.3f, -0.5f), vec2(1.0f, 1.0f)));
	currentAnimation = animateList[0];
	armor = LIGHT;
	maxHp = 1000;
	atk = 0;
	energy = 5;
	maxBlock = 10;
	cooldown = 5.0f;
	deadFrame = 6;
	attackRange.emplace_back(vec2(0.0f, 0.0f));
	attackRange.emplace_back(vec2(0.0f, 1.0f));
	addChild(attackCD = new Timer(Timer::COUNTDOWN, 0, false, Timer::FUNCNULL));
	addChild(airDefCD = new Timer(Timer::COUNTDOWN, 0, false, Timer::FUNCNULL));
}

GameObject* ShipBullin::createInstance() {
	return new ShipBullin();
}

string ShipBullin::getRarity() {
	return "SR";
}

bool ShipBullin::canSelected() {
	return false;
}

bool ShipBullin::hasSound() {
	return false;
}
