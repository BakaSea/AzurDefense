#include "SirenScavenger.h"

SirenScavenger::SirenScavenger() {
	name = "Scavenger";
	size = vec2(2.0f, 2.0f);
	animateList.emplace_back(new Animation("Move", 48, vec2(0.0f, -0.1f), vec2(1.0f / 0.7f, 1.0f / 0.7f)));
	animateList.emplace_back(new Animation("Attack", 8, vec2(0.0f, -0.1f), vec2(1.0f / 0.7f, 1.0f / 0.7f)));
	animateList.emplace_back(new Animation("Dead", 7, vec2(0.5f, -0.8f), vec2(1.0f / 0.7f, 1.0f / 0.7f)));
	currentAnimation = animateList[0];
	armor = LIGHT;
	maxHp = 1000;
	atk = 50;
	attackFrame = 3;
	deadFrame = 6;
	attackRange.emplace_back(vec2(0.0f, 1.0f));
	addChild(attackCD = new Timer(Timer::COUNTDOWN, 0, false, Timer::FUNCNULL));
	addChild(airDefCD = new Timer(Timer::COUNTDOWN, 0, false, Timer::FUNCNULL));
	velocity = 0.5f;
	energy = 2;
}

GameObject* SirenScavenger::createInstance() {
	return new SirenScavenger();
}
