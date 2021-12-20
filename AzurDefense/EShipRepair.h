#pragma once
#include "EnemyShip.h"

class EShipRepair : public EnemyShip {
public:
	EShipRepair();
	GameObject* createInstance() override;

protected:
	bool hasEnemyInRange() override;
	void doAttack() override;
};