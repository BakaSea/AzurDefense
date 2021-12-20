#include "ButtonNextChapter.h"
#include "Game.h"
#include "SceneMaps.h"

ButtonNextChapter::ButtonNextChapter() {
	name = "ButtonNextChapter";
	size = vec2(1.0f, 1.0f);
	clickable = true;
}

void ButtonNextChapter::render() {
	renderLowerChild();
	Texture2D* texture = Game::getInstance()->getResourceManager()->getTexture("UI/ButtonNextChapter");
	Game::getInstance()->getRenderer2D()->renderUI(texture, getPosition(), getRotateZ(), getSize(), getScaling(), vec2(0.0f, 0.0f), vec2(100.0f, 100.0f));
	renderUpperChild();
}

int ButtonNextChapter::click(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			SceneMaps* scene = dynamic_cast<SceneMaps*>(Game::getInstance()->getSceneController()->getCurrentScene());
			if (scene != nullptr) {
				scene->changeCurrentChapter(scene->getCurrentChapter() + 1);
			}
		}
	}
	return 0;
}
