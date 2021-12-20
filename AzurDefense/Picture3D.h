#pragma once
#include "Picture.h"
class Picture3D : public Picture {
public:
	Picture3D(string pictureName, vec2 size, vec2 drawPosition, vec2 drawSize);
	Picture3D(string name, string pictureName, vec2 size, vec2 drawPosition, vec2 drawSize);
	void render() override;
	bool is3D() override;
};