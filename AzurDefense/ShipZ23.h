#pragma once
#include "Ship.h"

class ShipZ23 : public Ship {
public:
	ShipZ23();
	GameObject* createInstance() override;
	string getRarity() override;
	bool isLongDistance() override;

protected:
	void doAttack() override;
	void doSkill() override;
};