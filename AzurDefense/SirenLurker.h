#pragma once
#include "Siren.h"

class SirenLurker : public Siren {
public:
	SirenLurker();
	GameObject* createInstance() override;

protected:
	void doAttack() override;
};