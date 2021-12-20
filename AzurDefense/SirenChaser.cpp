#include "SirenChaser.h"

SirenChaser::SirenChaser() {
	name = "Chaser";
	size = vec2(2.0f, 2.0f);
	animateList.emplace_back(new Animation("Move", 43, vec2(0.0f, -0.1f), vec2(1.0f / 0.6f, 1.0f / 0.6f)));
	animateList.emplace_back(new Animation("Attack", 8, vec2(0.0f, -0.15f), vec2(1.0f / 0.6f, 1.0f / 0.6f)));
	animateList.emplace_back(new Animation("Dead", 7, vec2(0.0f, -0.6f), vec2(1.0f / 0.6f, 1.0f / 0.6f)));
	currentAnimation = animateList[0];
	armor = LIGHT;
	maxHp = 2000;
	atk = 100;
	airDef = 200;
	attackFrame = 3;
	deadFrame = 6;
	attackRange = {
		vec2(0.0f, 0.0f), vec2(0.0f, 1.0f)
	};
	airDefRange = {
		vec2(-1.0f, -1.0f), vec2(-1.0f, 0.0f), vec2(-1.0f, 1.0f),
		vec2(0.0f, -1.0f), vec2(0.0f, 0.0f), vec2(0.0f, 1.0f),
		vec2(1.0f, -1.0f), vec2(1.0f, 0.0f), vec2(1.0f, 1.0f)
	};
	addChild(attackCD = new Timer(Timer::COUNTDOWN, 0, false, Timer::FUNCNULL));
	addChild(airDefCD = new Timer(Timer::COUNTDOWN, 2000, false, Timer::FUNCNULL));
	velocity = 0.35f;
	energy = 3;
}

GameObject* SirenChaser::createInstance() {
	return new SirenChaser();
}
