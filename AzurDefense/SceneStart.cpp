#include "SceneStart.h"
#include "Picture.h"
#include "ButtonStart.h"
#include "ButtonExit.h"
#include "ButtonContinue.h"
#include "Game.h"

SceneStart::SceneStart(int width, int height) : SceneBase(width, height) {
	btnContinue = nullptr;
}

void SceneStart::build() {
	mainCamera = new Camera(screenWidth, screenHeight, 90.0f, 0.1f, 50.0f);

	Picture* bgStart = new Picture("StartMenu", vec2(16.0f, 9.0f), vec2(0.0f, 0.0f), vec2(1024.0f, 576.0f));
	bgStart->setPosition(-8.0f, 4.5f);
	bgStart->setLayer(BACKGROUND);
	addObject(bgStart);

	Picture* logo = new Picture("Logo", vec2(4.0, 2.0f), vec2(0.0f, 0.0f), vec2(500.0f, 250.0f));
	logo->setPosition(-8.2f, 5.0f);
	logo->setLayer(UI);
	addObject(logo);

	Picture* bgButton = new Picture("ButtonAlpha", vec2(16.0f, 1.0f), vec2(0.0f, 0.0f), vec2(512.0f, 512.0f));
	bgButton->setPosition(-8.0f, -3.0f);
	bgButton->setLayer(UIBACKGROUND);
	addObject(bgButton);
	
	ButtonStart* btnStart = new ButtonStart();
	btnStart->setPosition(-5.0f, -3.25f);
	btnStart->setLayer(UI);
	addObject(btnStart);

	if (!Game::getInstance()->getResourceManager()->getUserData()->isFirstGame()) {
		btnContinue = new ButtonContinue();
		btnContinue->setPosition(-1.25f, -3.25f);
		btnContinue->setLayer(UI);
		addObject(btnContinue);
	}

	ButtonExit* btnExit = new ButtonExit();
	btnExit->setPosition(2.5f, -3.25f);
	btnExit->setLayer(UI);
	addObject(btnExit);
}

void SceneStart::start() {
	SceneBase::start();
	Game::getInstance()->getSoundEngine()->play2D(Game::getInstance()->getResourceManager()->getSound("BGMStart"), true);
}

void SceneStart::mouseCallback(GLFWwindow* window, int button, int action, int mods) {
	getWidgetList();
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	for (Widget* widget : widgetList) {
		vec3 point(0.0f);
		if (widget->is3D()) {
			MathHelper::Line ray = mainCamera->screenToWorldLine((float)x, (float)y);
			point = MathHelper::pointLinePlane(ray, widget->getPlane());
		} else {
			point = mainCamera->screenToUIPoint((float)x, (float)y);
		}
		if (widget->inBound(point)) {
			if (widget->canClick()) {
				int res = widget->click(window, button, action, mods);
				return;
			}
		}
	}
}

void SceneStart::changeNew() {
	Game::getInstance()->getSoundEngine()->stopAllSounds();
}

void SceneStart::changeBack() {
	if (btnContinue != nullptr) {
		removeObject(btnContinue);
	}
	if (!Game::getInstance()->getResourceManager()->getUserData()->isFirstGame()) {
		btnContinue = new ButtonContinue();
		btnContinue->setPosition(-1.25f, -3.25f);
		btnContinue->setLayer(UI);
		addObject(btnContinue);
	}
	Game::getInstance()->getSoundEngine()->play2D(Game::getInstance()->getResourceManager()->getSound("BGMStart"), true);
}
