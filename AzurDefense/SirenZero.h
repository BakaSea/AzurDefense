#pragma once
#include "Siren.h"

class SirenZero : public Siren {
public:
	SirenZero();
	GameObject* createInstance() override;
	bool isBoss() override;

protected:
	void doAttack() override;
	void doSkill() override;

private:
	int skillTime;
};

