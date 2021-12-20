#pragma once
#include "ButtonConfirm.h"
class ButtonConfirmPlayStop : public ButtonConfirm {
public:
	ButtonConfirmPlayStop();
	int click(GLFWwindow* window, int button, int action, int mods) override;
};