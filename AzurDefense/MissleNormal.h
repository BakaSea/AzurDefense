#pragma once
#include "ThrowingObject.h"

class MissleNormal : public ThrowingObject {
public:
	MissleNormal();
	GameObject* createInstance() override;
};