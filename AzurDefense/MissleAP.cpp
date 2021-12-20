#include "MissleAP.h"
#include "Character.h"

MissleAP::MissleAP() {
	name = "MissleAP";
	size = vec2(0.5f, 0.5f);
}

GameObject* MissleAP::createInstance() {
	return new MissleAP();
}

float MissleAP::calculateDamage(GameObject* object) {
	Character* charac = dynamic_cast<Character*>(object);
	if (charac != nullptr) {
		Character::ARMOR armor = charac->getArmor();
		float rate = 1.0f;
		switch (armor) {
		case Character::LIGHT: rate = 0.4f; break;
		case Character::MIDDIUM: rate = 1.4f; break;
		case Character::HEAVY: rate = 1.2f; break;
		}
		return rate * damage;
	} else return damage;
}
