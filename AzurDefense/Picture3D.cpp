#include "Picture3D.h"
#include "Texture2D.h"
#include "Game.h"

Picture3D::Picture3D(string pictureName, vec2 size, vec2 drawPosition, vec2 drawSize) :
	Picture(pictureName, size, drawPosition, drawSize) {

}

Picture3D::Picture3D(string name, string pictureName, vec2 size, vec2 drawPosition, vec2 drawSize) :
	Picture3D(pictureName, size, drawPosition, drawSize) {
	this->name = name;
}

void Picture3D::render() {
	renderLowerChild();
	Texture2D* texture = Game::getInstance()->getResourceManager()->getTexture("UI/" + pictureName);
	Game::getInstance()->getRenderer2D()->renderUI3D(texture, getPosition(), getSize(), getRotateX(), getRotateY(), getRotateZ(), getScaling(),
		drawPosition, drawSize);
	renderUpperChild();
}

bool Picture3D::is3D() {
	return true;
}
