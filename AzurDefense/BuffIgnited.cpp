#include "BuffIgnited.h"
#include "Character.h"

BuffIgnited::BuffIgnited() {
	init();
}

BuffIgnited::BuffIgnited(int damage) : BuffBase(15000) {
	init();
	this->damage = damage;
}

void BuffIgnited::startBuff() {
	addChild(new Timer(Timer::INTERVAL, 3000, false, [this]() {
		if (dynamic_cast<Character*>(parentObject) != nullptr) {
			Character* charac = (Character*)parentObject;
			charac->getDamaged(damage);
		}
		}));
}

void BuffIgnited::init() {
	damage = 0;
	name = "BuffIgnited";
	size = vec2(1.0f, 1.0f);
}
