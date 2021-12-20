#pragma once
#include "GameObject.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "MathHelper.h"
using namespace glm;

class Camera : public GameObject {
public:
	Camera(int width, int height, float fov, float near, float far);
	void render() override;
	void setPosition(vec3 position) override;
	void setPosition(float x, float y, float z) override;
	float getPitch();
	void setRotation(float pitch, float yaw);
	mat4 getViewMatrix();
	mat4 getProjectionMatrix();
	mat4 getUIMatrix();
	vec3 getFront();
	MathHelper::Line screenToWorldLine(vec2 point);
	MathHelper::Line screenToWorldLine(float x, float y);
	vec3 screenToUIPoint(vec2 point);
	vec3 screenToUIPoint(float x, float y);
private:
	vec3 front, right, up, worldUp;
	float screenWidth, screenHeight, screenFov, screenAspect, screenNear, screenFar;
	float yaw, pitch;
	void updateCameraVectors();
};