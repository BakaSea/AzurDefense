#pragma once
#include "AirCraft.h"

class ACTorpedo : public AirCraft {
public:
	ACTorpedo();
	GameObject* createInstance() override;

protected:
	void doAttack() override;
};

