#include "MissleNormal.h"

MissleNormal::MissleNormal() {
	name = "MissleNormal";
	size = vec2(0.5f, 0.5f);
}

GameObject* MissleNormal::createInstance() {
	return new MissleNormal();
}
