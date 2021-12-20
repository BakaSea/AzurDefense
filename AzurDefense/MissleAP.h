#pragma once
#include "MissleNormal.h"
class MissleAP : public MissleNormal {
public:
	MissleAP();
	GameObject* createInstance() override;

protected:
	float calculateDamage(GameObject* object) override;
};

