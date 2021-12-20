#pragma once
#include "Siren.h"

class SirenPurifier : public Siren {
public:
	SirenPurifier();
	GameObject* createInstance() override;
	bool isBoss() override;

protected:
	void doAttack() override;
	void doSkill() override;
};

