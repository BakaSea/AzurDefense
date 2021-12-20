#pragma once
#include "Siren.h"

class EnemyShip : public Siren {
public:
	EnemyShip();

protected:
	bool isDead() override;
};
