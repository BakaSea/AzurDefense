#pragma once
#include "Character.h"
#include "AirCraft.h"

class Kansen : public Character {
public:
	Kansen();

protected:
	void createAircraft(AirCraft* aircraft, int acAtk, int acAirDef, int acHp, bool acBellicose, vec2 offset, int delay);
	void attackEnemy() override;
};

