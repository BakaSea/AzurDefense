#pragma once
#include "BuffBase.h"

class BuffDamagedImpRate : public BuffBase {
public:
	BuffDamagedImpRate();
	BuffDamagedImpRate(float rate, int lasting);

protected:
	void init() override;
	void startBuff() override;
	void endBuff() override;

private:
	float rate;
};

