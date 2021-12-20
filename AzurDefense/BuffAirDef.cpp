#include "BuffAirDef.h"

BuffAirDef::BuffAirDef() : BuffBase(300) {
	init();
}

void BuffAirDef::init() {
	name = "BuffAirDef";
	size = vec2(2.0f, 2.0f);
	animateList.emplace_back(currentAnimation = new Animation("AirDef", 3, vec2(0.0f, 0.25f), vec2(1.0f, 1.0f)));
}

void BuffAirDef::startBuff() {
	currentAnimation->play();
}
