#include "PlatformObstacle.h"

PlatformObstacle::PlatformObstacle() {
	name = "PlatformObstacle";
}

GameObject* PlatformObstacle::createInstance() {
	return new PlatformObstacle();
}
