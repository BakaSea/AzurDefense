#pragma once
#include "Widget.h"
class ButtonStart : public Widget {
public:
	ButtonStart();
	int click(GLFWwindow* window, int button, int action, int mods) override;
	void render() override;
};
