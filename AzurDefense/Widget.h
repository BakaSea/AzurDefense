#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GameObject.h"

class Widget : public GameObject {
public:
	Widget();
	void setPosition(vec2 position);
	void setPosition(float x, float y);
	void setPosition(vec3 position);
	void setRotation(float rotation);
	void setRotation(float rotateX, float rotateY, float rotateZ);
	virtual void render() override;
	virtual bool is3D();
	bool inBound(vec3 point) override;
	bool canClick();
	virtual int click(GLFWwindow* window, int button, int action, int mods);

protected:
	bool clickable;
};
