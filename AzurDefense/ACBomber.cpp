#include "ACBomber.h"
#include "Bomb.h"

ACBomber::ACBomber() {
	name = "AircraftBomber";
	size = vec2(1.0f, 1.0f);
	attackRange.emplace_back(vec2(0.0f, 0.0f));
	addChild(airDefCD = new Timer(Timer::COUNTDOWN, 0, false, Timer::FUNCNULL));
}

GameObject* ACBomber::createInstance() {
	return new ACBomber();
}

void ACBomber::doAttack() {
	createThrowingObject(new Bomb(), getPosition() + vec3(0.0f, -1.0f, 0.0f), 0.2f, 0.5f, calculateDamage(nullptr), 1, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f));
}
