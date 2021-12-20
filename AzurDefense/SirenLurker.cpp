#include "SirenLurker.h"
#include "Torpedo.h"

SirenLurker::SirenLurker() {
	name = "Lurker";
	size = vec2(2.0f, 2.0f);
	animateList.emplace_back(new Animation("Move", 10, vec2(0.0f, -0.1f), vec2(1.0f / 0.8f, 1.0f / 0.8f)));
	animateList.emplace_back(new Animation("Attack", 4, vec2(0.0f, -0.2f), vec2(1.0f / 0.8f, 1.0f / 0.8f)));
	animateList.emplace_back(new Animation("Dead", 6, vec2(0.0f, -0.5f), vec2(1.0f / 0.8f, 1.0f / 0.8f)));
	currentAnimation = animateList[0];
	armor = LIGHT;
	maxHp = 1000;
	atk = 100;
	airDef = 0;
	attackFrame = 2;
	deadFrame = 5;
	attackRange = {
		vec2(0.0f, 1.0f), vec2(0.0f, 2.0f), vec2(0.0f, 3.0f), vec2(0.0f, 4.0f), vec2(0.0f, 5.0f)
	};
	addChild(attackCD = new Timer(Timer::COUNTDOWN, 2000, false, Timer::FUNCNULL));
	addChild(airDefCD = new Timer(Timer::COUNTDOWN, 0, false, Timer::FUNCNULL));
	velocity = 0.3f;
	energy = 2;
}

GameObject* SirenLurker::createInstance() {
	return new SirenLurker();
}

void SirenLurker::doAttack() {
	createThrowingObject(new Torpedo(), 0.0f, 1.0f, calculateDamage(nullptr), 1, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f));
}
