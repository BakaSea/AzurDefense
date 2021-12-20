#pragma once
#include "ThrowingObject.h"
class Torpedo : public ThrowingObject {
public:
	Torpedo();
	GameObject* createInstance() override;

protected:
	void doAttack(GameObject* object) override;
	float calculateDamage(GameObject* object) override;
};

