#pragma once
#include "Siren.h"
class SirenChaser : public Siren {
public:
	SirenChaser();
	GameObject* createInstance() override;
};

