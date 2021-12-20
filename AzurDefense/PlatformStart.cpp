#include "PlatformStart.h"

PlatformStart::PlatformStart() {
	name = "PlatformStart";
}

GameObject* PlatformStart::createInstance() {
	return new PlatformStart();
}
