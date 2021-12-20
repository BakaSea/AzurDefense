#include "ButtonConfirmPlayStop.h"
#include "Game.h"

ButtonConfirmPlayStop::ButtonConfirmPlayStop() {
	name = "ButtonConfirmPlayStop";
}

int ButtonConfirmPlayStop::click(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			Game::getInstance()->getSceneController()->changePrevScene();
			return 1;
		}
	}
	return 0;
}
