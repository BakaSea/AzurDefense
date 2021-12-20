#pragma once
#include "BuffBase.h"

class BuffHeal : public BuffBase {
public:
	BuffHeal();
	BuffHeal(int healHp);

protected:
	void startBuff() override;
	void init() override;

private:
	int healHp;
};
