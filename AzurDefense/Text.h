#pragma once
#include "Widget.h"

class Text : public Widget {
public:
	Text();
	void render() override;
	void setText(string text);
	void setScale(float scale);
	void setColor(vec3 color);
	void setColor(float red, float green, float blue);

protected:
	string text;
	float scale;
	vec3 color;
};