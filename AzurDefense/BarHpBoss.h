#pragma once
#include "Widget.h"

class BarHpBoss : public Widget {
public:
	BarHpBoss(bool left);
	void render() override;

private:
	bool left;
};