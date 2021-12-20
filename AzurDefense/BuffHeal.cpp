#include "BuffHeal.h"
#include "Character.h"

BuffHeal::BuffHeal() {
	init();
}

BuffHeal::BuffHeal(int healHp) : BuffBase(1000) {
	init();
	this->healHp = healHp;
}

void BuffHeal::startBuff() {
	if (dynamic_cast<Character*>(parentObject)) {
		Character* charac = (Character*)parentObject;
		charac->addHp(healHp);
		currentAnimation->play();
	}
}

void BuffHeal::init() {
	healHp = 0;
	name = "BuffHeal";
	size = vec2(1.0f, 1.0f);
	animateList.emplace_back(currentAnimation = new Animation("Heal", 3, vec2(0.0f, 0.25f), vec2(1.0f, 1.0f)));
}
