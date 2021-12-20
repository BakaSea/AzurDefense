#include "ACFighter.h"
#include "Bomb.h"

ACFighter::ACFighter() {
	name = "AircraftFighter";
	size = vec2(1.0f, 1.0f);
	attackRange.emplace_back(vec2(0.0f, 0.0f));
	airDefRange.emplace_back(vec2(0.0f, 1.0f));
	airDefRange.emplace_back(vec2(0.0f, 2.0f));
	addChild(airDefCD = new Timer(Timer::COUNTDOWN, 1000, false, Timer::FUNCNULL));
}

GameObject* ACFighter::createInstance() {
	return new ACFighter();
}

void ACFighter::doAttack() {
	createThrowingObject(new Bomb(), getPosition() + vec3(0.0f, -1.0f, 0.0f), 0.2f, 0.5f, calculateDamage(nullptr), 1, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f));
}
