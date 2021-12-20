#include "PlatformLong.h"

PlatformLong::PlatformLong() {
	name = "PlatformLong";
}

GameObject* PlatformLong::createInstance() {
	return new PlatformLong();
}
