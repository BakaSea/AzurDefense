#pragma once
#include "Platform.h"

class PlatformShort : public Platform {
public:
	PlatformShort();
	GameObject* createInstance() override;
};

