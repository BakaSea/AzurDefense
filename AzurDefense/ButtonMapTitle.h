#pragma once
#include "Widget.h"

class ButtonMapTitle : public Widget {
public:
	ButtonMapTitle(pair<int, int> mapID);
	void render() override;
	virtual int click(GLFWwindow* window, int button, int action, int mods) override;

private:
	pair<int, int> mapID;
};
