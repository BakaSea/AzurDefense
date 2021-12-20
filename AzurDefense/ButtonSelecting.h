#pragma once
#include "Widget.h"
#include "Character.h"

class ButtonSelecting : public Widget {
public:
	ButtonSelecting();
	void start() override;
	void render() override;
	int click(GLFWwindow* window, int button, int action, int mods) override;
	bool is3D() override;

private:
	Character::ORIENT orientation;
	float orientDegree;
	void setOrient(Character::ORIENT orient);
};
