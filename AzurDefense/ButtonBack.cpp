#include "ButtonBack.h"
#include "Game.h"

ButtonBack::ButtonBack() {
	name = "ButtonBack";
	size = vec2(1.0f, 1.0f);
	clickable = true;
}

void ButtonBack::render() {
	renderLowerChild();
	Texture2D* texture = Game::getInstance()->getResourceManager()->getTexture("UI/ButtonBack");
	Game::getInstance()->getRenderer2D()->renderUI(texture, getPosition(), getRotateZ(), getSize(), getScaling(), vec2(0.0f, 0.0f), vec2(154.0f, 154.0f));
	renderUpperChild();
}

int ButtonBack::click(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			Game::getInstance()->getSceneController()->changePrevScene();
			return 1;
		}
	}
	return 0;
}
