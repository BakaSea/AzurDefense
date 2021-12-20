#include "Bomb.h"

Bomb::Bomb() {
	name = "Bomb";
	size = vec2(0.25f, 0.25f);
	radius = 1.2f;
}

GameObject* Bomb::createInstance() {
	return new Bomb();
}
