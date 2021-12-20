#include "SceneLoading.h"
#include "Picture.h"
#include "Game.h"
#include "SceneStart.h"
#include "BarLoading.h"

SceneLoading::SceneLoading(int width, int height) : SceneBase(width, height) {

}

void SceneLoading::build() {
	mainCamera = new Camera(screenWidth, screenHeight, 90.0f, 0.1f, 50.0f);
	
	Picture* bgStart = new Picture("StartMenu", vec2(16.0f, 9.0f), vec2(0.0f, 0.0f), vec2(1024.0f, 576.0f));
	bgStart->setPosition(-8.0f, 4.5f);
	bgStart->setLayer(BACKGROUND);
	addObject(bgStart);

	Picture* logo = new Picture("Logo", vec2(4.0, 2.0f), vec2(0.0f, 0.0f), vec2(500.0f, 250.0f));
	logo->setPosition(-8.2f, 5.0f);
	logo->setLayer(UI);
	addObject(logo);

	BarLoading* barLoading = new BarLoading();
	barLoading->setPosition(-8.0f, -4.5f + barLoading->getSize().y);
	barLoading->setLayer(UI);
	addObject(barLoading);
}

void SceneLoading::start() {
	SceneBase::start();
}

void SceneLoading::update() {
	if (Game::getInstance()->getRegistration()->getCurrentRegistry() == Game::getInstance()->getRegistration()->getRegistrySize()) {
		Game::getInstance()->getSceneController()->changeNewScene(new SceneStart(screenWidth, screenHeight));
	} else {
		Game::getInstance()->getRegistration()->init();
	}
}
