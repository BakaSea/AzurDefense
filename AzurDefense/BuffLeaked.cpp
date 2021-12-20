#include "BuffLeaked.h"
#include "Character.h"

BuffLeaked::BuffLeaked() {
	init();
}

BuffLeaked::BuffLeaked(int damage) : BuffBase(15000) {
	init();
	this->damage = damage;
}

void BuffLeaked::startBuff() {
	addChild(new Timer(Timer::INTERVAL, 3000, false, [this]() {
		if (dynamic_cast<Character*>(parentObject) != nullptr) {
			Character* charac = (Character*)parentObject;
			charac->getDamaged(damage);
		}
		}));
}

void BuffLeaked::init() {
	damage = 0;
	name = "BuffLeaked";
	size = vec2(1.0f, 1.0f);
}
