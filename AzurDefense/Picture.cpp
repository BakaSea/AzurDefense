#include "Picture.h"
#include "Texture2D.h"
#include "Game.h"

Picture::Picture(string pictureName, vec2 size, vec2 drawPosition, vec2 drawSize) {
	this->name = "Picture";
	this->size = size;
	this->pictureName = pictureName;
	this->drawPosition = drawPosition;
	this->drawSize = drawSize;
}

Picture::Picture(string name, string pictureName, vec2 size, vec2 drawPosition, vec2 drawSize) :
	Picture(pictureName, size, drawPosition, drawSize) {
	this->name = name;
}

void Picture::render() {
	renderLowerChild();
	Texture2D* texture = Game::getInstance()->getResourceManager()->getTexture("UI/" + pictureName);
	Game::getInstance()->getRenderer2D()->renderUI(texture, getPosition(), getRotateZ(), getSize(), getScaling(), drawPosition, drawSize);
	renderUpperChild();
}

string Picture::getPictureName() {
	return pictureName;
}
