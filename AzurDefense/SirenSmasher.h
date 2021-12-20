#pragma once
#include "Siren.h"

class SirenSmasher : public Siren {
public:
	SirenSmasher();
	GameObject* createInstance() override;

protected:
	void doAttack() override;
};