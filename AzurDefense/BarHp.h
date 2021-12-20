#pragma once
#include "Widget.h"

class BarHp : public Widget {
public:
	BarHp();
	void render() override;
	bool is3D() override;
};
