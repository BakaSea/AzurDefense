#pragma once
#include "BuffBase.h"

class BuffAirDefImpRate : public BuffBase {
public:
	BuffAirDefImpRate();
	BuffAirDefImpRate(float rate, int lasting);

protected:
	void init() override;
	void startBuff() override;
	void endBuff() override;

private:
	float rate;
};

