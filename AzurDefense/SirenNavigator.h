#pragma once
#include "Siren.h"

class SirenNavigator : public Siren {
public:
	SirenNavigator();
	GameObject* createInstance() override;

protected:
	void doAttack() override;
};

