#pragma once
#include "Widget.h"

class ButtonExit : public Widget {
public:
	ButtonExit();
	int click(GLFWwindow* window, int button, int action, int mods) override;
	void render() override;
};
