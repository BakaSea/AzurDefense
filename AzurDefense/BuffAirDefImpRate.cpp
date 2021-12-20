#include "BuffAirDefImpRate.h"
#include "Character.h"

BuffAirDefImpRate::BuffAirDefImpRate() {
	init();
}

BuffAirDefImpRate::BuffAirDefImpRate(float rate, int lasting) : BuffBase(lasting) {
	init();
	this->rate = rate;
}

void BuffAirDefImpRate::init() {
	name = "BuffAirDefImpRate";
	rate = 0.0f;
}

void BuffAirDefImpRate::startBuff() {
	if (dynamic_cast<Character*>(parentObject)) {
		Character* charac = (Character*)parentObject;
		charac->incAirDefImpRate(rate);
	}
}

void BuffAirDefImpRate::endBuff() {
	if (dynamic_cast<Character*>(parentObject)) {
		Character* charac = (Character*)parentObject;
		charac->decAirDefImpRate(rate);
	}
}
