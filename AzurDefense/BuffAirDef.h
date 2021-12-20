#pragma once
#include "BuffBase.h"

class BuffAirDef : public BuffBase {
public:
	BuffAirDef();

protected:
	void init() override;
	void startBuff() override;
};