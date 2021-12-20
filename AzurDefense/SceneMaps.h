#pragma once
#include "SceneBase.h"
#include "ButtonMapTitle.h"
#include "ButtonPrevChapter.h"
#include "ButtonNextChapter.h"

class SceneMaps : public SceneBase {
public:
	enum LAYER {
		BACKGROUND = 0,
		UI = 50
	};
	SceneMaps(int width, int height);
	void start() override;
	void build() override;
	void mouseCallback(GLFWwindow* window, int button, int action, int mods) override;
	void changeNew() override;
	void changeBack() override;
	int getCurrentChapter();
	void changeCurrentChapter(int chapter);

private:
	int currentChapter;
	vector<ButtonMapTitle*> btnMapTitleList;
	ButtonPrevChapter* btnPrev;
	ButtonNextChapter* btnNext;
	void updateBtnMapTitleList();
};