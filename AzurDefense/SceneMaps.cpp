#include "SceneMaps.h"
#include "Game.h"
#include "ButtonBack.h"
#include "Picture.h"
#include "Text.h"

SceneMaps::SceneMaps(int width, int height) : SceneBase(width, height) {
	currentChapter = 1;
	btnMapTitleList.clear();
	btnNext = nullptr;
	btnPrev = nullptr;
}

void SceneMaps::start() {
	SceneBase::start();
	Game::getInstance()->getSoundEngine()->play2D(Game::getInstance()->getResourceManager()->getSound("BGMMap"), true);
}

void SceneMaps::build() {
	mainCamera = new Camera(screenWidth, screenHeight, 90.0f, 0.1f, 50.0f);

	Picture* bg = new Picture("BGMap", vec2(16.0f, 9.0f), vec2(0.0f, 0.0f), vec2(1024.0f, 576.0f));
	bg->setLayer(BACKGROUND);
	bg->setPosition(-8.0f, 4.5f);
	addObject(bg);

	ButtonBack* btnBack = new ButtonBack();
	btnBack->setLayer(UI);
	btnBack->setPosition(-8.0f, 4.5f);
	addObject(btnBack);

	updateBtnMapTitleList();
}

void SceneMaps::mouseCallback(GLFWwindow* window, int button, int action, int mods) {
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
				string widgetName = widget->getName();
				int res = widget->click(window, button, action, mods);
				if (res) {
					return;
				}
			}
		}
	}
}

void SceneMaps::changeNew() {
	Game::getInstance()->getSoundEngine()->stopAllSounds();
}

void SceneMaps::changeBack() {
	updateBtnMapTitleList();
	Game::getInstance()->getSoundEngine()->play2D(Game::getInstance()->getResourceManager()->getSound("BGMMap"), true);
}

int SceneMaps::getCurrentChapter() {
	return currentChapter;
}

void SceneMaps::changeCurrentChapter(int chapter) {
	currentChapter = chapter;
	updateBtnMapTitleList();
}

void SceneMaps::updateBtnMapTitleList() {
	for (auto btn : btnMapTitleList) {
		removeChild(btn);
	}
	btnMapTitleList.clear();
	removeChild(btnPrev);
	removeChild(btnNext);
	int mapSize = Game::getInstance()->getResourceManager()->getMapManager()->getMapSize(currentChapter);
	for (int i = 1; i <= mapSize; ++i) {
		pair<int, int> mapID = make_pair(currentChapter, i);
		if (Game::getInstance()->getResourceManager()->getUserData()->isMapReach(mapID)) {
			ButtonMapTitle* btn = new ButtonMapTitle(mapID);
			btn->setLayer(UI);
			btn->setPosition(Game::getInstance()->getResourceManager()->getMapManager()->getPosition(mapID));
			addObject(btn);
			btnMapTitleList.emplace_back(btn);
			Text* text = new Text();
			text->setText(to_string(currentChapter) + "-" + to_string(i));
			text->setLayer(1);
			text->setPosition(1.9f, -1.15f);
			text->setScale(0.01f);
			btn->addChild(text);
		} else break;
	}
	if (currentChapter != 1) {
		btnPrev = new ButtonPrevChapter();
		btnPrev->setLayer(UI);
		btnPrev->setPosition(-8.0f, 0.5f);
		addObject(btnPrev);
	}
	if (currentChapter != Game::getInstance()->getResourceManager()->getMapManager()->getChapterSize()) {
		if (Game::getInstance()->getResourceManager()->getUserData()->isMapClear(make_pair(currentChapter, mapSize))) {
			btnNext = new ButtonNextChapter();
			btnNext->setLayer(UI);
			btnNext->setPosition(7.0f, 0.5f);
			addObject(btnNext);
		}
	}
}
