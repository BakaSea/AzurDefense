#pragma once
#include "Ship.h"

class ShipKashino : public Ship {
public:
	ShipKashino();
	GameObject* createInstance() override;
	string getRarity() override;

protected:
	void doSkill() override;
};
