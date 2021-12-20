#include "Platform.h"

Platform::Platform() {
	name = "Platform";
	size = vec2(1.0f, 1.0f);
	location = vec2(0.0f, 0.0f);
}

GameObject* Platform::createInstance() {
	return new Platform();
}

vec2 Platform::getLocation() {
	return location;
}

void Platform::setLocation(vec2 location) {
	this->location = location;
}

void Platform::setLocation(int x, int y) {
	setLocation(vec2(x, y));
}

