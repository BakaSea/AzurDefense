#pragma once
#include "Widget.h"

class ButtonNextChapter : public Widget {
public:
	ButtonNextChapter();
	void render() override;
	int click(GLFWwindow* window, int button, int action, int mods) override;
};

