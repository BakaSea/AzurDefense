#pragma once
#include "BuffBase.h"

class BuffIgnited : public BuffBase {
public:
	BuffIgnited();
	BuffIgnited(int damage);

protected:
	void startBuff() override;
	void init() override;

private:
	int damage;
};