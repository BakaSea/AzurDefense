#pragma once
#include "Ship.h"

class ShipShimakaze : public Ship {
public:
	ShipShimakaze();
	GameObject* createInstance() override;
	string getRarity() override;

protected:
	void doSkill() override;
};