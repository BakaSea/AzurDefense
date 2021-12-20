#pragma once
#include "Widget.h"
#include "Ship.h"

class ButtonSelectCard : public Widget {
public:
	ButtonSelectCard(Ship* ship);
	~ButtonSelectCard();
	int click(GLFWwindow* window, int button, int action, int mods) override;
	void update() override;
	void render() override;
	void clearCooldown();
	string getShipName();

private:
	Ship* ship;
	float cdCount;
	bool selected;
};
