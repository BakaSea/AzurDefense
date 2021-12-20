#include "Widget.h"
#include "Game.h"

Widget::Widget() {
	clickable = false;
}

void Widget::setPosition(vec2 position) {
	GameObject::setPosition(vec3(position, 0.0f));
}

void Widget::setPosition(float x, float y) {
	setPosition(vec2(x, y));
}

void Widget::setPosition(vec3 position) {
	GameObject::setPosition(position);
}

void Widget::setRotation(float rotation) {
	rotateZ = rotation;
}

void Widget::setRotation(float rotateX, float rotateY, float rotateZ) {
	GameObject::setRotation(rotateX, rotateY, rotateZ);
}

void Widget::render() {
	renderLowerChild();
	renderUpperChild();
}

bool Widget::is3D() {
	return false;
}

bool Widget::inBound(vec3 point) {
	vec4 p(point, 1.0f);
	mat4 model = MathHelper::getModelMatrix(getPosition(), getRotateX(), getRotateY(), getRotateZ(), size, getScaling());
	p = inverse(model) * p;
	return 0.0f <= p.x && p.x <= 1.0f && -1.0f <= p.y && p.y <= 0.0f;
}

bool Widget::canClick() {
	return clickable;
}

int Widget::click(GLFWwindow* window, int button, int action, int mods) {
	return 0;
}
