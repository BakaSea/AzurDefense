#include "ACTorpedo.h"
#include "Torpedo.h"

ACTorpedo::ACTorpedo() {
	name = "AircraftTorpedo";
	size = vec2(1.0f, 1.0f);
	attackRange.emplace_back(vec2(0.0f, 2.0f));
	addChild(airDefCD = new Timer(Timer::COUNTDOWN, 0, false, Timer::FUNCNULL));
}

GameObject* ACTorpedo::createInstance() {
	return new ACTorpedo();
}

void ACTorpedo::doAttack() {
	createThrowingObject(new Torpedo(), 5.0f, 1.0f, calculateDamage(nullptr), 3, vec2(0.0f, -1.0f), vec2(1.0f, 1.0f));
}
