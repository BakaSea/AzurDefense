#include "ShipShimakaze.h"
#include "Torpedo.h"
#include "MissleNormal.h"

ShipShimakaze::ShipShimakaze() {
	name = "Shimakaze";
	size = vec2(2.0f, 2.0f);
	animateList.emplace_back(new Animation("Drag", 8, vec2(0.0f, -0.3f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Stand", 18, vec2(0.0f, -0.1f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Attack", 8, vec2(0.0f, -0.1f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Dead", 7, vec2(0.3f, -0.5f), vec2(1.0f / 0.8f, 1.0f / 0.8f)));
	animateList.emplace_back(new Animation("Skill", 8, vec2(0.0f, -0.1f), vec2(1.0f, 1.0f), true));
	currentAnimation = animateList[0];
	armor = LIGHT;
	maxHp = 1790;
	atk = 500;
	energy = 20;
	maxBlock = 3;
	cooldown = 20.0f;
	attackFrame = 3;
	deadFrame = 6;
	attackRange = {
		vec2(0.0f, 0.0f), vec2(0.0f, 1.0f)
	};
	addChild(attackCD = new Timer(Timer::COUNTDOWN, 0, false, Timer::FUNCNULL));
	addChild(airDefCD = new Timer(Timer::COUNTDOWN, 0, false, Timer::FUNCNULL));
	addChild(skillCD = new Timer(Timer::COUNTDOWN, 20000, false, Timer::FUNCNULL));
}

GameObject* ShipShimakaze::createInstance() {
	return new ShipShimakaze();
}

string ShipShimakaze::getRarity() {
	return "UR";
}

void ShipShimakaze::doSkill() {
	createThrowingObject(new MissleNormal(), 2.0f, 3.5f, calculateDamage(nullptr) / 3.0f, 3, vec2(0.5f, 0.3f), vec2(1.0f, 1.0f));
	createThrowingObject(new Torpedo(), 2.0f, 3.0f, calculateDamage(nullptr) / 5.0f, 5, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f));
	Timer* t1 = new Timer(Timer::COUNTDOWN, 1000, false, Timer::FUNCNULL);
	t1->setFunc([this, t1]() {
		createThrowingObject(new Torpedo(), 5.0f, 3.0f, calculateDamage(nullptr), 5, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f));
		removeChild(t1);
		});
	addChild(t1);
}
