#include "ShipJavelin.h"
#include "DebugHelper.h"

ShipJavelin::ShipJavelin() {
	name = "Javelin";
	size = vec2(2.0f, 2.0f);
	animateList.emplace_back(new Animation("Drag", 5, vec2(0.0f, -0.3f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Stand", 8, vec2(0.0f, -0.3f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Attack", 8, vec2(0.0f, -0.3f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Dead", 7, vec2(0.3f, -0.5f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Skill", 8, vec2(0.0f, -0.3f), vec2(1.0f, 1.0f), true));
	currentAnimation = animateList[0];
	armor = LIGHT;
	maxHp = 1200;
	atk = 150;
	airDef = 200;
	energy = 5;
	maxBlock = 0;
	cooldown = 5.0f;
	attackFrame = 1;
	deadFrame = 6;
	attackRange.emplace_back(vec2(0.0f, 0.0f));
	attackRange.emplace_back(vec2(0.0f, 1.0f));
	airDefRange.emplace_back(vec2(-1.0f, -1.0f));
	airDefRange.emplace_back(vec2(-1.0f, 0.0f));
	airDefRange.emplace_back(vec2(-1.0f, 1.0f));
	airDefRange.emplace_back(vec2(0.0f, -1.0f));
	airDefRange.emplace_back(vec2(0.0f, 0.0f));
	airDefRange.emplace_back(vec2(0.0f, 1.0f));
	airDefRange.emplace_back(vec2(1.0f, -1.0f));
	airDefRange.emplace_back(vec2(1.0f, 0.0f));
	airDefRange.emplace_back(vec2(1.0f, 1.0f));
	addChild(attackCD = new Timer(Timer::COUNTDOWN, 0, false, Timer::FUNCNULL));
	addChild(airDefCD = new Timer(Timer::COUNTDOWN, 2000, false, Timer::FUNCNULL));
	addChild(skillCD = new Timer(Timer::COUNTDOWN, 20000, false, Timer::FUNCNULL));
	addChild(timerSkill = new Timer(Timer::COUNTDOWN, 8000, true, Timer::FUNCNULL));
}

GameObject* ShipJavelin::createInstance() {
	return new ShipJavelin();
}

string ShipJavelin::getRarity() {
	return "SR";
}

void ShipJavelin::getDamaged(float damage) {
	if (!timerSkill->timeOut()) {
		float rate = float(rand()) / float(RAND_MAX);
		if (rate <= 0.5f) {
			Character::getDamaged(damage);
		}
	} else {
		Character::getDamaged(damage);
	}
}

void ShipJavelin::doSkill() {
	timerSkill->start();
}
