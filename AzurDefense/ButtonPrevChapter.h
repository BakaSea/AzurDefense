#pragma once
#include "Widget.h"

class ButtonPrevChapter : public Widget {
public:
	ButtonPrevChapter();
	void render() override;
	int click(GLFWwindow* window, int button, int action, int mods) override;
};