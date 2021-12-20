#pragma once
#include "GameObject.h"

class ThrowingObject : public GameObject {
public:
	ThrowingObject();
	void start() override;
	virtual void update() override;
	void enableGravity();
	void disableGravity();
	void setEnemy(bool fromEnemy);
	void setDamage(float damage);
	void aim(vec3 source, vec3 velocity);
	void aim(vec3 source, vec3 target, float time);

protected:
	bool hasGravity, fromEnemy;
	vec3 velocity, g;
	int totalTime;
	float damage, radius;
	virtual void doAttack(GameObject* object);
	virtual float calculateDamage(GameObject* object);
	void changeRotation();
};