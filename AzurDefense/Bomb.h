#pragma once
#include "ThrowingObject.h"

class Bomb : public ThrowingObject {
public:
	Bomb();
	GameObject* createInstance() override;
};
