#include "ButtonExit.h"
#include "Game.h"

ButtonExit::ButtonExit() {
	name = "ButtonExit";
	size = vec2(2.5f, 0.5f);
	clickable = true;
}

int ButtonExit::click(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			Game::getInstance()->stop();
		}
	}
	return 0;
}

void ButtonExit::render() {
	Texture2D* texture = Game::getInstance()->getResourceManager()->getTexture("UI/ButtonExit");
	Game::getInstance()->getRenderer2D()->renderUI(texture, getPosition(), getRotateZ(), size, getScaling(), vec2(0.0f, 0.0f), vec2(200.0f, 40.0f));
}
