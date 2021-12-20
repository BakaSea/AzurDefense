#pragma once
#include "Kansen.h"

class Siren : public Kansen {
public:
	Siren();
	virtual void update() override;
	bool isEnemy() override;
	void setRoute(int id);
	virtual bool isBoss();
	void useSkill() override;

protected:
	int routeID, routeIndex;
	float velocity;
	virtual bool hasEnemyInRange() override;
};

