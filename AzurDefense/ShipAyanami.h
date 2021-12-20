#pragma once
#include "Ship.h"

class ShipAyanami : public Ship {
public:
	ShipAyanami();
	GameObject* createInstance() override;
	string getRarity() override;

protected:
	void doSkill() override;
};
