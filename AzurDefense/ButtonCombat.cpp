#include "ButtonCombat.h"
#include "Game.h"
#include "ScenePlay.h"

ButtonCombat::ButtonCombat() {
	name = "ButtonCombat";
	size = vec2(2.48f, 1.0f);
	clickable = true;
}

void ButtonCombat::render() {
	renderLowerChild();
	Texture2D* texture = Game::getInstance()->getResourceManager()->getTexture("UI/ButtonCombat");
	Game::getInstance()->getRenderer2D()->renderUI(texture, getPosition(), getRotateZ(), getSize(), getScaling(), vec2(0.0f, 0.0f), vec2(347.0f, 140.0f));
	renderUpperChild();
}

int ButtonCombat::click(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			ScenePlay* scene = dynamic_cast<ScenePlay*>(Game::getInstance()->getSceneController()->getCurrentScene());
			if (scene != nullptr) {
				scene->run();
				return 1;
			}
		}
	}
	return 0;
}
