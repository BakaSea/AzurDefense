#pragma once
#include "Widget.h"

class ContainerShip : public Widget {
public:
	ContainerShip();
	void start() override;
	void render() override;

private:
	const int COL;
};

