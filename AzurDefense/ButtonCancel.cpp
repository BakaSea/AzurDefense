#include "ButtonCancel.h"
#include "Game.h"

ButtonCancel::ButtonCancel() {
	name = "ButtonCancel";
	size = vec2(1.4f, 0.52f);
	clickable = true;
}

void ButtonCancel::render() {
	renderLowerChild();
	Texture2D* texture = Game::getInstance()->getResourceManager()->getTexture("UI/Info/Cancel");
	Game::getInstance()->getRenderer2D()->renderUI(texture, getPosition(), getRotateZ(), getSize(), getScaling(), vec2(0.0f, 0.0f), vec2(175.0f, 65.0f));
	renderUpperChild();
}

int ButtonCancel::click(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			parentObject->remove();
			return 1;
		}
	}
	return 0;
}
