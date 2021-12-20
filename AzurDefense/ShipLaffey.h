#pragma once
#include "Ship.h"

class ShipLaffey : public Ship {
public:
	ShipLaffey();
	GameObject* createInstance() override;
	string getRarity() override;
	bool isLongDistance() override;

protected:
	void doSkill() override;
	void doAttack() override;
};
