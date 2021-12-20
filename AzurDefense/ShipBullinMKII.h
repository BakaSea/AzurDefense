#pragma once
#include "Ship.h"

class ShipBullinMKII : public Ship {
public:
	ShipBullinMKII();
	GameObject* createInstance() override;
	string getRarity() override;
	bool isLongDistance() override;

protected:
	bool hasEnemyInRange() override;
	void doAttack() override;
	void doSkill() override;

private:
	vector<vec2> placeLocList;
};

