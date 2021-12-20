#pragma once
#include "GameObject.h"

class Navigation : public GameObject {
public:
	Navigation();
	void start() override;
	void update() override;
	GameObject* createInstance() override;
	void setRoute(int id);

private:
	int routeID, routeIndex;
	float velocity;
};

