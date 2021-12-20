#pragma once
#include "BuffBase.h"

class BuffLeaked : public BuffBase {
public:
	BuffLeaked();
	BuffLeaked(int damage);

protected:
	void startBuff() override;
	void init() override;

private:
	int damage;
};

