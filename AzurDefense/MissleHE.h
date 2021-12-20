#pragma once
#include "MissleNormal.h"
class MissleHE : public MissleNormal {
public:
	MissleHE();
	GameObject* createInstance() override;

protected:
	void doAttack(GameObject* object) override;
	float calculateDamage(GameObject* object) override;
};

