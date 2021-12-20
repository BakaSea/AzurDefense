#pragma once
#include "Platform.h"

class PlatformLong : public Platform {
public:
	PlatformLong();
	GameObject* createInstance() override;
};

