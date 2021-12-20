#include "ButtonContinue.h"
#include "Game.h"
#include "SceneMaps.h"

ButtonContinue::ButtonContinue() {
	name = "ButtonContinue";
	size = vec2(2.5f, 0.5f);
	clickable = true;
}

void ButtonContinue::render() {
	renderLowerChild();
	Texture2D* texture = Game::getInstance()->getResourceManager()->getTexture("UI/ButtonContinue");
	Game::getInstance()->getRenderer2D()->renderUI(texture, getPosition(), getRotateZ(), getSize(), getScaling(), vec2(0.0f, 0.0f), vec2(200.0f, 40.0f));
	renderUpperChild();
}

int ButtonContinue::click(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			Game::getInstance()->getSceneController()->changeNewScene(new SceneMaps(Game::getInstance()->screenWidth, Game::getInstance()->screenHeight));
			return 1;
		}
	}
	return 0;
}
