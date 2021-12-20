#pragma once
#include "SceneBase.h"
#include "ButtonContinue.h"

class SceneStart : public SceneBase {
public:
	SceneStart(int width, int height);
	void build() override;
	void start() override;
	void mouseCallback(GLFWwindow* window, int button, int action, int mods) override;
	void changeNew() override;
	void changeBack() override;

private:
	enum LAYER {
		BACKGROUND = 0,
		UIBACKGROUND = 50,
		UI = 51
	};
	ButtonContinue* btnContinue;
};