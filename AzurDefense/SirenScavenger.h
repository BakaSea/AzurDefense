#pragma once
#include "Siren.h"

class SirenScavenger : public Siren {
public:
	SirenScavenger();
	GameObject* createInstance() override;
};
