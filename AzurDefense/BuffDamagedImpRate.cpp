#include "BuffDamagedImpRate.h"
#include "Character.h"

BuffDamagedImpRate::BuffDamagedImpRate() {
	init();
}

BuffDamagedImpRate::BuffDamagedImpRate(float rate, int lasting) : BuffBase(lasting) {
	init();
	this->rate = rate;
}

void BuffDamagedImpRate::init() {
	name = "BuffDamagedImpRate";
	rate = 0.0f;
}

void BuffDamagedImpRate::startBuff() {
	if (dynamic_cast<Character*>(parentObject)) {
		Character* charac = (Character*)parentObject;
		charac->incDamagedImpRate(rate);
	}
}

void BuffDamagedImpRate::endBuff() {
	if (dynamic_cast<Character*>(parentObject)) {
		Character* charac = (Character*)parentObject;
		charac->decDamagedImpRate(rate);
	}
}
