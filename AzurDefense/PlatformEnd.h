#pragma once
#include "Platform.h"

class PlatformEnd : public Platform {
public:
	PlatformEnd();
	GameObject* createInstance() override;
};
