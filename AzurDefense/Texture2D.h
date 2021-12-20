#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
using namespace glm;

class Texture2D {
public:
	Texture2D();
	Texture2D(const char* texturePath);
	void bindTexture();
	vec2 getSize();

private:
	GLuint textureID;
	GLint width, height, nrChannels;
};

