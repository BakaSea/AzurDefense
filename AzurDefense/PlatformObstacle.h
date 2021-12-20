#pragma once
#include "Platform.h"

class PlatformObstacle : public Platform {
public:
	PlatformObstacle();
	GameObject* createInstance() override;
};
