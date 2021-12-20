#pragma once
#include "AirCraft.h"

class ACFighter : public AirCraft {
public:
	ACFighter();
	GameObject* createInstance() override;

protected:
	void doAttack() override;
};

