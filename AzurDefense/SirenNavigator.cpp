#include "SirenNavigator.h"
#include "MissleNormal.h"

SirenNavigator::SirenNavigator() {
	name = "Navigator";
	size = vec2(2.0f, 2.0f);
	animateList.emplace_back(new Animation("Move", 23, vec2(0.0f, -0.1f), vec2(1.0f / 0.7f, 1.0f / 0.7f)));
	animateList.emplace_back(new Animation("Attack", 8, vec2(0.0f, -0.1f), vec2(1.0f / 0.7f, 1.0f / 0.7f)));
	animateList.emplace_back(new Animation("Dead", 7, vec2(0.0f, -0.3f), vec2(1.0f / 0.7f, 1.0f / 0.7f)));
	currentAnimation = animateList[0];
	armor = MIDDIUM;
	maxHp = 3000;
	atk = 200;
	airDef = 200;
	attackFrame = 3;
	deadFrame = 6;
	attackRange = {
		vec2(0.0f, 0.0f), vec2(0.0f, 1.0f), vec2(0.0f, 2.0f), vec2(0.0f, 3.0f), vec2(0.0f, 4.0f)
	};
	airDefRange = {
		vec2(-1.0f, -1.0f), vec2(-1.0f, 0.0f), vec2(-1.0f, 1.0f),
		vec2(0.0f, -1.0f), vec2(0.0f, 0.0f), vec2(0.0f, 1.0f),
		vec2(1.0f, -1.0f), vec2(1.0f, 0.0f), vec2(1.0f, 1.0f)
	};
	addChild(attackCD = new Timer(Timer::COUNTDOWN, 3000, false, Timer::FUNCNULL));
	addChild(airDefCD = new Timer(Timer::COUNTDOWN, 2000, false, Timer::FUNCNULL));
	velocity = 0.25f;
	energy = 4;
}

GameObject* SirenNavigator::createInstance() {
	return new SirenNavigator();
}

void SirenNavigator::doAttack() {
	createThrowingObject(new MissleNormal(), 5.0f, 3.0f, calculateDamage(nullptr) / 3.0f, 3, vec2(0.5f, 0.3f), vec2(1.5f, 1.5f));
}
