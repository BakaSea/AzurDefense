#include "MissleHE.h"
#include "Character.h"
#include "BuffIgnited.h"

MissleHE::MissleHE() {
	name = "MissleHE";
	size = vec2(0.5f, 0.5f);
}

GameObject* MissleHE::createInstance() {
	return new MissleHE();
}

void MissleHE::doAttack(GameObject* object) {
	if (dynamic_cast<Character*>(object) != nullptr) {
		Character* charac = (Character*)object;
		charac->getDamaged(calculateDamage(charac));
		float ignitedRate = float(rand()) / float(RAND_MAX);
		if (ignitedRate <= 0.25f) {
			BuffIgnited* buff = new BuffIgnited(damage * 0.1f);
			buff->setLayer(1);
			charac->addChild(buff);
		}
	}
}

float MissleHE::calculateDamage(GameObject* object) {
	Character* charac = dynamic_cast<Character*>(object);
	if (charac != nullptr) {
		Character::ARMOR armor = charac->getArmor();
		float rate = 1.0f;
		switch (armor) {
		case Character::LIGHT: rate = 1.4f; break;
		case Character::MIDDIUM: rate = 1.1f; break;
		case Character::HEAVY: rate = 0.9f; break;
		}
		return rate * damage;
	} else return damage;
}
