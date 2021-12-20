#pragma once
#include "GameObject.h"
#include <set>
#include "ThrowingObject.h"
#include "Timer.h"

class Character : public GameObject {
public:
	enum STATUS {
		DRAG,
		STAND,
		MOVE,
		ATTACK,
		DEAD,
		SKILL
	};
	enum ORIENT {
		RIGHT = 0,
		DOWN = 1,
		LEFT = 2,
		UP = 3
	};
	enum ARMOR {
		LIGHT,
		MIDDIUM,
		HEAVY
	};
	Character();
	virtual ~Character();
	virtual void start() override;
	void render() override;
	virtual GameObject* createInstance() override;
	vec2 getLocation();
	void setLocation(vec2 location);
	void setLocation(int x, int y);
	virtual bool isEnemy();
	STATUS getStatus();
	virtual void setStatus(STATUS status);
	ORIENT getOrient();
	void setOrient(ORIENT orient);
	virtual void getDamaged(float damage);
	int getHp();
	int getMaxHp();
	int getEnergy();
	vector<vec2> getAttackRange();
	vector<vec2> getAirDefRange();
	int getMaxBlock();
	ARMOR getArmor();
	void addHp(int hp);
	int getAttack();
	void incAtkImpRate(float rate);
	void decAtkImpRate(float rate);
	int getAirDef();
	void incAirDefImpRate(float rate);
	void decAirDefImpRate(float rate);
	Timer* getSkillCD();
	virtual void useSkill();
	void incDamagedImpRate(float rate);
	void decDamagedImpRate(float rate);

protected:
	vec2 location;
	ARMOR armor;
	int maxHp, hp, atk, airDef, energy, maxBlock;
	float critRate, critDamage, atkImpRate, airDefImpRate, damagedImpRate;
	STATUS status;
	vector<vec2> attackRange, airDefRange;
	ORIENT orientation;
	float orientDegree;
	vector<Character*> enemyList, aircraftList;
	int attackFrame, deadFrame;
	Timer* attackCD, * airDefCD, * damagedTimer, * skillCD;
	bool hasAttacked;
	vec3 getFront();
	void createThrowingObject(ThrowingObject* obj, float angle, float velocity, float damage, int num, vec2 offset, vec2 scaling);
	void createThrowingObject(ThrowingObject* obj, vec3 target, float radius, float time, float damage, int num, vec2 offset, vec2 scaling);
	bool hasAirCraftInRange();
	virtual bool hasEnemyInRange();
	virtual void attackAirCraft();
	virtual void attackEnemy();
	virtual void doAttack();
	float calculateDamage(GameObject* object);
	virtual void doSkill();
	virtual bool isDead();
};
