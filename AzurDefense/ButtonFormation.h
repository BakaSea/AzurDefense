#pragma once
#include "Widget.h"
#include "ContainerShip.h"

class ButtonFormation : public Widget {
public:
	ButtonFormation();
	void render() override;
	int click(GLFWwindow* window, int button, int action, int mods) override;

private:
	ContainerShip* container;
};

