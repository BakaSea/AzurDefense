#pragma once
#include "Character.h"

class AirCraft : public Character {
public:
	AirCraft();
	void update() override;
	void setStatus(STATUS status) override;
	bool isEnemy() override;
	void setEnemy(bool fromEnemy);
	void setAttack(int atk);
	void setMaxHp(int maxHp);
	void setAirDef(int airDef);
	void setHp(int hp);
	void setFront(vec2 front);
	void setBellicose(bool bellicose);
	void setCharacter(bool fromCharacter);

protected:
	bool fromEnemy, bellicose, suicide, fromCharacter;
	float velocity;
	vec2 front;
	bool hasEnemyInRange() override;
	void attackAirCraft() override;
	void attackEnemy() override;
	void explode();
};