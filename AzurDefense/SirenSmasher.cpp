#include "SirenSmasher.h"
#include "MissleHE.h"

SirenSmasher::SirenSmasher() {
	name = "Smasher";
	size = vec2(2.0f, 2.0f);
	animateList.emplace_back(new Animation("Move", 24, vec2(0.0f, 0.0f), vec2(1.0f / 0.5f, 1.0f / 0.5f)));
	animateList.emplace_back(new Animation("Attack", 8, vec2(0.0f, 0.0f), vec2(1.0f / 0.5f, 1.0f / 0.5f)));
	animateList.emplace_back(new Animation("Dead", 7, vec2(0.0f, -0.8f), vec2(1.0f / 0.4f, 1.0f / 0.4f)));
	currentAnimation = animateList[0];
	armor = HEAVY;
	maxHp = 5000;
	atk = 600;
	airDef = 100;
	attackFrame = 5;
	deadFrame = 6;
	attackRange = {
		vec2(0.0f, 1.0f), vec2(0.0f, 2.0f), vec2(0.0f, 3.0f), vec2(0.0f, 4.0f)
	};
	airDefRange = {
		vec2(-1.0f, -1.0f), vec2(-1.0f, 0.0f), vec2(-1.0f, 1.0f),
		vec2(0.0f, -1.0f), vec2(0.0f, 0.0f), vec2(0.0f, 1.0f),
		vec2(1.0f, -1.0f), vec2(1.0f, 0.0f), vec2(1.0f, 1.0f)
	};
	addChild(attackCD = new Timer(Timer::COUNTDOWN, 10000, false, Timer::FUNCNULL));
	addChild(airDefCD = new Timer(Timer::COUNTDOWN, 2000, false, Timer::FUNCNULL));
	velocity = 0.15f;
	energy = 5;
}

GameObject* SirenSmasher::createInstance() {
	return new SirenSmasher();
}

void SirenSmasher::doAttack() {
	int index = rand() % enemyList.size();
	createThrowingObject(new MissleHE(), enemyList[index]->getPosition(), 0.2f, 
		MathHelper::getFlyingTime(getPosition(), enemyList[index]->getPosition()), calculateDamage(nullptr) / 2.0f, 2, vec2(0.5f, 0.3f), vec2(2.0f, 2.0f));
}
