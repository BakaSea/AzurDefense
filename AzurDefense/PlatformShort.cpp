#include "PlatformShort.h"

PlatformShort::PlatformShort() {
	name = "PlatformShort";
}

GameObject* PlatformShort::createInstance() {
	return new PlatformShort();
}
