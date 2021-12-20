#pragma once
#include "Widget.h"

class ButtonCancel : public Widget {
public:
	ButtonCancel();
	void render() override;
	virtual int click(GLFWwindow* window, int button, int action, int mods) override;
};
