#include "ButtonConfirm.h"
#include "Game.h"

ButtonConfirm::ButtonConfirm() {
	name = "ButtonConfirm";
	size = vec2(1.4f, 0.52f);
	clickable = true;
}

void ButtonConfirm::render() {
	renderLowerChild();
	Texture2D* texture = Game::getInstance()->getResourceManager()->getTexture("UI/Info/Confirm");
	Game::getInstance()->getRenderer2D()->renderUI(texture, getPosition(), getRotateZ(), getSize(), getScaling(), vec2(0.0f, 0.0f), vec2(175.0f, 65.0f));
	renderUpperChild();
}

int ButtonConfirm::click(GLFWwindow* window, int button, int action, int mods) {
	return 0;
}