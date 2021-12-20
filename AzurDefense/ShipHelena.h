#pragma once
#include "Ship.h"

class ShipHelena : public Ship {
public:
	ShipHelena();
	GameObject* createInstance() override;
	string getRarity() override;
	bool isLongDistance() override;

protected:
	void doAttack() override;
	void doSkill() override;
};

