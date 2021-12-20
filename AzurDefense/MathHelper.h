#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <utility>
#include <functional>
#include <string>
using namespace glm;
using namespace std;

class MathHelper {
public:
	typedef pair<vec3, vec3> Line;
	typedef vec4 Plane;
	static vec3 pointLinePlane(Line line, Plane plane);
	static Plane getPlane(vec3 normal, vec3 point);
	static mat4 getModelMatrix(vec3 position, float rotateX, float rotateY, float rotateZ, vec2 size, vec2 scaling);
	static vec2 getRandomCirclePoint();
	static float getFlyingTime(vec3 source, vec3 target);
	static int getRarityPriority(string rarity);
};
