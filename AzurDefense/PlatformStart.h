#pragma once
#include "Platform.h"
class PlatformStart : public Platform {
public:
	PlatformStart();
	GameObject* createInstance() override;
};