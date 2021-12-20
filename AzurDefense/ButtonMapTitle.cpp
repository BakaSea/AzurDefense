#include "ButtonMapTitle.h"
#include "Game.h"
#include "ScenePlay.h"

ButtonMapTitle::ButtonMapTitle(pair<int, int> mapID) {
	name = "ButtonMapTitle";
	size = vec2(4.0f, 2.0f);
	clickable = true;
	this->mapID = mapID;
}

void ButtonMapTitle::render() {
	renderLowerChild();
	Texture2D* texture = nullptr;
	if (Game::getInstance()->getResourceManager()->getUserData()->isMapClear(mapID)) {
		texture = Game::getInstance()->getResourceManager()->getTexture("UI/MapTitleClear");
	} else {
		texture = Game::getInstance()->getResourceManager()->getTexture("UI/MapTitleUnclear");
	}
	Game::getInstance()->getRenderer2D()->renderUI(texture, getPosition(), getRotateZ(), getSize(), getScaling(), vec2(0.0f, 0.0f), vec2(400.0f, 200.0f));
	renderUpperChild();
}

int ButtonMapTitle::click(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			Game::getInstance()->getSceneController()->changeNewScene(new ScenePlay(mapID, Game::getInstance()->screenWidth, Game::getInstance()->screenHeight));
			return 1;
		}
	}
	return 0;
}
