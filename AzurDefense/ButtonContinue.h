#pragma once
#include "Widget.h"

class ButtonContinue : public Widget {
public:
	ButtonContinue();
	void render() override;
	virtual int click(GLFWwindow* window, int button, int action, int mods) override;
};

