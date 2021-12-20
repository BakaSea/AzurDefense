#pragma once
#include "Ship.h"

class ShipJavelin : public Ship {
public:
	ShipJavelin();
	GameObject* createInstance() override;
	string getRarity() override;
	void getDamaged(float damage) override;

protected:
	void doSkill() override;

private:
	Timer* timerSkill;
};