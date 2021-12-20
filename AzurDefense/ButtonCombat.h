#pragma once
#include "Widget.h"

class ButtonCombat : public Widget {
public:
	ButtonCombat();
	void render() override;
	int click(GLFWwindow* window, int button, int action, int mods) override;
};

