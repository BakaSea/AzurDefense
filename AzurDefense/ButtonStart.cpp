#include "ButtonStart.h"
#include "Game.h"
#include "ScenePlay.h"
#include "SceneMaps.h"

ButtonStart::ButtonStart() {
	name = "ButtonStart";
	size = vec2(2.5f, 0.5f);
	clickable = true;
}

int ButtonStart::click(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			Game::getInstance()->getResourceManager()->initUserData();
			Game::getInstance()->getSceneController()->changeNewScene(new SceneMaps(Game::getInstance()->screenWidth, Game::getInstance()->screenHeight));
			return 1;
		}
	}
	return 0;
}

void ButtonStart::render() {
	renderLowerChild();
	Texture2D* texture = Game::getInstance()->getResourceManager()->getTexture("UI/ButtonStart");
	Game::getInstance()->getRenderer2D()->renderUI(texture, getPosition(), getRotateZ(), size, getScaling(), vec2(0.0f, 0.0f), vec2(200.0f, 40.0f));
	renderUpperChild();
}
