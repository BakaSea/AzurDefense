#pragma once
#include "Widget.h"

class Picture : public Widget {
public:
	Picture(string pictureName, vec2 size, vec2 drawPosition, vec2 drawSize);
	Picture(string name, string pictureName, vec2 size, vec2 drawPosition, vec2 drawSize);
	void render() override;
	string getPictureName();

protected:
	string pictureName;
	vec2 drawPosition, drawSize;
};
