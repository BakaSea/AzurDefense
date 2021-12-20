#pragma once
#include "Ship.h"
class ShipNagato : public Ship {
public:
	ShipNagato();
	GameObject* createInstance() override;
	string getRarity() override;
	bool isLongDistance() override;

protected:
	void doAttack() override;
	void doSkill() override;
};

