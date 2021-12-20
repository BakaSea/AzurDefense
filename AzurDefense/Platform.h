#pragma once
#include "GameObject.h"

class Platform : public GameObject {
public:
	Platform();
	virtual GameObject* createInstance() override;
	vec2 getLocation();
	void setLocation(vec2 location);
	void setLocation(int x, int y);
private:
	vec2 location;
};
