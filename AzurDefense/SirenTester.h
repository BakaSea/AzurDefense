#pragma once
#include "Siren.h"

class SirenTester : public Siren {
public:
	SirenTester();
	GameObject* createInstance() override;
	bool isBoss() override;

protected:
	void doAttack() override;
	void doSkill() override;

private:
	bool skillTimes;
};