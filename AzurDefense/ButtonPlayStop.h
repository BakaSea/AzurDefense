#pragma once
#include "Widget.h"

class ButtonPlayStop : public Widget {
public:
	ButtonPlayStop();
	void render() override;
	int click(GLFWwindow* window, int button, int action, int mods) override;
};
