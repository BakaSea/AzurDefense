#include "ButtonPlayStop.h"
#include "Game.h"
#include "ScenePlay.h"
#include "ButtonInfo.h"
#include "ButtonCancel.h"
#include "ButtonConfirmPlayStop.h"

ButtonPlayStop::ButtonPlayStop() {
	name = "ButtonPlayStop";
	size = vec2(0.5f, 0.5f);
	clickable = true;
}

void ButtonPlayStop::render() {
	renderLowerChild();
	Texture2D* texture = Game::getInstance()->getResourceManager()->getTexture("UI/ButtonPlayStop");
	Game::getInstance()->getRenderer2D()->renderUI(texture, getPosition(), getRotateZ(), getSize(), getScaling(), vec2(0.0f, 0.0f), vec2(200.0f, 200.0f));
	renderUpperChild();
}

int ButtonPlayStop::click(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			ScenePlay* scene = dynamic_cast<ScenePlay*>(Game::getInstance()->getSceneController()->getCurrentScene());
			if (scene != nullptr) {
				scene->stop();
				ButtonInfo* btnInfo = new ButtonInfo("InfoPlayStop", new ButtonCancel(), new ButtonConfirmPlayStop());
				btnInfo->setLayer(ScenePlay::UIRESULT);
				scene->addObject(btnInfo);
				return 1;
			}
		}
	}
	return 0;
}
