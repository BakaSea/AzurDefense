#pragma once
#include "BuffBase.h"
class BuffAtkImpRate : public BuffBase {
public:
	BuffAtkImpRate();
	BuffAtkImpRate(float rate, int lasting);

protected:
	void init() override;
	void startBuff() override;
	void endBuff() override;

private:
	float rate;
};

