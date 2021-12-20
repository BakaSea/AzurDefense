#include "Torpedo.h"
#include "Character.h"
#include "BuffLeaked.h"

Torpedo::Torpedo() {
    name = "Torpedo";
    size = vec2(0.5f, 0.5f);
    hasGravity = false;
}

GameObject* Torpedo::createInstance() {
    return new Torpedo();
}

void Torpedo::doAttack(GameObject* object) {
	if (dynamic_cast<Character*>(object) != nullptr) {
		Character* charac = (Character*)object;
		charac->getDamaged(calculateDamage(charac));
		float ignitedRate = float(rand()) / float(RAND_MAX);
		if (ignitedRate <= 0.25f) {
			BuffLeaked* buff = new BuffLeaked(damage * 0.1f);
			buff->setLayer(1);
			charac->addChild(buff);
		}
	}
}

float Torpedo::calculateDamage(GameObject* object) {
	Character* charac = dynamic_cast<Character*>(object);
	if (charac != nullptr) {
		Character::ARMOR armor = charac->getArmor();
		float rate = 1.0f;
		switch (armor) {
		case Character::LIGHT: rate = 0.8f; break;
		case Character::MIDDIUM: rate = 1.0f; break;
		case Character::HEAVY: rate = 1.3f; break;
		}
		return rate * damage;
	} else return damage;
}
