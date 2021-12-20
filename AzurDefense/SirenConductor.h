#pragma once
#include "Siren.h"

class SirenConductor : public Siren {
public:
	SirenConductor();
	GameObject* createInstance() override;

protected:
	void doAttack() override;
};

