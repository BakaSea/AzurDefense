#pragma once
#include "Kansen.h"

class Ship : public Kansen {
public:
	Ship();
	virtual void start() override;
	virtual void update() override;
	virtual string getRarity();
	float getCooldown();
	virtual bool isLongDistance();
	virtual bool canSelected();
	virtual bool hasSound();

protected:
	bool playSetSound;
	float cooldown;
	bool hasEnemyInRange() override;
};

