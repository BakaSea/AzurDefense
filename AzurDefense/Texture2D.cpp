#include "Texture2D.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include "DebugHelper.h"

Texture2D::Texture2D() {
	textureID = 0;
	width = height = nrChannels = 0;
}

Texture2D::Texture2D(const char* texturePath) {
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_set_flip_vertically_on_load(true);
	GLubyte* data = stbi_load(texturePath, &width, &height, &nrChannels, STBI_rgb_alpha);
	if (data == NULL) {
		DebugHelper::logError("Failed to load texture " + string(texturePath));
	} else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	stbi_image_free(data);
}

void Texture2D::bindTexture() {
	glBindTexture(GL_TEXTURE_2D, textureID);
}

vec2 Texture2D::getSize() {
	return vec2(width, height);
}
