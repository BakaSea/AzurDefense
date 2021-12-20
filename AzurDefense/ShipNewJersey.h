#pragma once
#include "Ship.h"

class ShipNewJersey : public Ship {
public:
	ShipNewJersey();
	GameObject* createInstance() override;
	string getRarity() override;
	bool isLongDistance() override;

protected:
	void doAttack() override;
	void doSkill() override;
};

