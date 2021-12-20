#pragma once
#include "Ship.h"

class ShipSaratoga : public Ship {
public:
	ShipSaratoga();
	GameObject* createInstance() override;
	string getRarity() override;
	bool isLongDistance() override;

protected:
	void doAttack() override;
	void doSkill() override;
};

