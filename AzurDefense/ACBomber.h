#pragma once
#include "AirCraft.h"

class ACBomber : public AirCraft {
public:
	ACBomber();
	GameObject* createInstance() override;

protected:
	void doAttack() override;
};

