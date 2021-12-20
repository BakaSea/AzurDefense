#pragma once
#include "Ship.h"
class ShipCheshire : public Ship {
public:
	ShipCheshire();
	GameObject* createInstance() override;
	bool isLongDistance() override;
	string getRarity() override;

protected:
	void doAttack();
	void doSkill();
};

