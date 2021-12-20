#pragma once
#include "Widget.h"
class ButtonConfirm : public Widget {
public:
	ButtonConfirm();
	void render() override;
	virtual int click(GLFWwindow* window, int button, int action, int mods) override;
};