#include "PlatformEnd.h"

PlatformEnd::PlatformEnd() {
	name = "PlatformEnd";
}

GameObject* PlatformEnd::createInstance() {
	return new PlatformEnd();
}
