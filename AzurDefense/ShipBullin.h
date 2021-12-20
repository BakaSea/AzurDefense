#pragma once
#include "Ship.h"

class ShipBullin : public Ship {
public:
	ShipBullin();
	GameObject* createInstance() override;
	string getRarity() override;
	bool canSelected() override;
	bool hasSound() override;
};
