#pragma once
#include "Widget.h"

class ButtonBack : public Widget {
public:
	ButtonBack();
	void render() override;
	virtual int click(GLFWwindow* window, int button, int action, int mods) override;
};