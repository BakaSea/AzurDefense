#include "BuffAtkImpRate.h"
#include "Character.h"

BuffAtkImpRate::BuffAtkImpRate() {
	init();
}

BuffAtkImpRate::BuffAtkImpRate(float rate, int lasting) : BuffBase(lasting) {
	init();
	this->rate = rate;
}

void BuffAtkImpRate::init() {
	name = "BuffAtkImpRate";
	rate = 0.0f;
}

void BuffAtkImpRate::startBuff() {
	if (dynamic_cast<Character*>(parentObject)) {
		Character* charac = (Character*)parentObject;
		charac->incAtkImpRate(rate);
	}
}

void BuffAtkImpRate::endBuff() {
	if (dynamic_cast<Character*>(parentObject)) {
		Character* charac = (Character*)parentObject;
		charac->decAtkImpRate(rate);
	}
}
