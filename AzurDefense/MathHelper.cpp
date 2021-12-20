#include "MathHelper.h"
#include <glm/gtc/matrix_transform.hpp>
#include <time.h>
#include "DebugHelper.h"

vec3 MathHelper::pointLinePlane(Line line, Plane plane) {
	float a = line.first.x, b = line.first.y, c = line.first.z,
		x0 = line.second.x, y0 = line.second.y, z0 = line.second.z,
		A = plane.x, B = plane.y, C = plane.z, D = plane.w;
	float t = -(A * x0 + B * y0 + C * z0 + D) / (A * a + B * b + C * c);
	return vec3(x0 + a * t, y0 + b * t, z0 + c * t);
}

MathHelper::Plane MathHelper::getPlane(vec3 normal, vec3 point) {
	Plane result(0.0f);
	result.x = normal.x;
	result.y = normal.y;
	result.z = normal.z;
	result.w = -dot(normal, point);
	return result;
}

mat4 MathHelper::getModelMatrix(vec3 position, float rotateX, float rotateY, float rotateZ, vec2 size, vec2 scaling) {
	mat4 model(1.0f);
	model = translate(model, position);
	model = rotate(model, radians(rotateX), vec3(1.0f, 0.0f, 0.0f));
	model = rotate(model, radians(rotateY), vec3(0.0f, 1.0f, 0.0f));
	model = rotate(model, radians(rotateZ), vec3(0.0f, 0.0f, 1.0f));
	model = scale(model, vec3(size, 1.0f));
	model = scale(model, vec3(scaling, 1.0f));
	return model;
}

vec2 MathHelper::getRandomCirclePoint() {
	vec2 result(0.0f);
	do {
		result.x = float(rand()) / float(RAND_MAX) - 0.5f;
		result.y = float(rand()) / float(RAND_MAX) - 0.5f;
	} while (length(result) > 1.0f);
	return result;
}

float MathHelper::getFlyingTime(vec3 source, vec3 target) {
	return length(target - source) * 0.3f;
}

int MathHelper::getRarityPriority(string rarity) {
	if (rarity == "R") return 0;
	if (rarity == "SR") return 1;
	if (rarity == "SSR") return 2;
	if (rarity == "UR") return 3;
	return -1;
}
