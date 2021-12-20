#include "Camera.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "DebugHelper.h"
using namespace glm;

Camera::Camera(int width, int height, float fov, float near, float far) {
	screenWidth = (float)width;
	screenHeight = (float)height;
	screenFov = fov;
	screenAspect = screenWidth/screenHeight;
	screenNear = near;
	screenFar = far;
	yaw = pitch = 0.0f;
	position = vec3(0.0f, 0.0f, 0.0f);
	worldUp = up = vec3(0.0f, 1.0f, 0.0f);
}

void Camera::render() {
	renderLowerChild();
	renderUpperChild();
}

void Camera::setPosition(vec3 position) {
	GameObject::setPosition(position);
	updateCameraVectors();
}

void Camera::setPosition(float x, float y, float z) {
	setPosition(vec3(x, y, z));
}

float Camera::getPitch() {
	return pitch;
}

void Camera::setRotation(float pitch, float yaw) {
	this->pitch = pitch;
	this->yaw = yaw;
	updateCameraVectors();
}

mat4 Camera::getViewMatrix() {
	return lookAt(position, position + front, up);
}

mat4 Camera::getProjectionMatrix() {
	return perspective(radians(screenFov), screenAspect, screenNear, screenFar);
}

mat4 Camera::getUIMatrix() {
	mat4 UImatrix(1.0f);
	UImatrix[0][0] = 1.0f / 8.0f;
	UImatrix[1][1] = 1.0f / 4.5f;
	return UImatrix;
}

vec3 Camera::getFront() {
	return front;
}

MathHelper::Line Camera::screenToWorldLine(vec2 point) {
	vec3 v1(0.0f), v2(0.0f);
	v1.x = v2.x = point.x;
	v1.y = v2.y = screenHeight - point.y;
	v1.z = 0.1f;
	v2.z = 1.0f;
	vec4 viewport(0.0f, 0.0f, screenWidth, screenHeight);
	mat4 view = getViewMatrix(), projection = getProjectionMatrix();
	v1 = unProject(v1, view, projection, viewport);
	v2 = unProject(v2, view, projection, viewport);
	vec3 v = normalize(v2 - v1);
	return make_pair(v, position);
}

MathHelper::Line Camera::screenToWorldLine(float x, float y) {
	return screenToWorldLine(vec2(x, y));
}

vec3 Camera::screenToUIPoint(vec2 point) {
	vec4 v(0.0f);
	v.x = 2 * point.x / screenWidth - 1.0f;
	v.y = 1.0f - 2 * point.y / screenHeight;
	v.w = 1.0f;
	mat4 ui = getUIMatrix();
	return inverse(ui) * v;
}

vec3 Camera::screenToUIPoint(float x, float y) {
	return screenToUIPoint(vec2(x, y));
}

void Camera::updateCameraVectors() {
	vec3 tmp;
	tmp.x = cos(radians(yaw)) * cos(radians(pitch));
	tmp.y = sin(radians(pitch));
	tmp.z = sin(radians(yaw)) * cos(radians(pitch));
	front = normalize(tmp);
	right = normalize(cross(front, worldUp));
	up = normalize(cross(right, front));
}
