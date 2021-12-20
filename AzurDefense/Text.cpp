#include "Text.h"
#include "Game.h"

Text::Text() {
	name = "Text";
	size = vec2(1.0f, 1.0f);
	text = "";
	scale = 1.0f;
	color = vec3(1.0f, 1.0f, 1.0f);
}

void Text::render() {
	renderLowerChild();
	Game::getInstance()->getRenderer2D()->renderText(text, getPosition(), getRotateZ(), scale, color);
	renderUpperChild();
}

void Text::setText(string text) {
	this->text = text;
}

void Text::setScale(float scale) {
	this->scale = scale;
}

void Text::setColor(vec3 color) {
	this->color = color;
}

void Text::setColor(float red, float green, float blue) {
	setColor(vec3(red, green, blue));
}
