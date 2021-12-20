#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <map>
#include "Shader.h"
#include "Texture2D.h"
using namespace glm;
using namespace std;

class Renderer2D {
public:
	enum MODE {
		FONT = 0,
		MIDDLE = 1,
		BOTTOM = 2,
		LEFTTOP = 3
	};
	Renderer2D();
	Renderer2D(const Renderer2D& A);
	~Renderer2D();
	void render(Texture2D* texture, vec3 position, vec2 size, GLfloat rotateX, GLfloat rotateY, GLfloat rotateZ, vec2 scaling, MODE mode);
	void renderUI(Texture2D* texture, vec2 position, float rotation, vec2 size, vec2 scaling, vec2 drawPos, vec2 drawSize);
	void renderUI3D(Texture2D* texture, vec3 position, vec2 size, GLfloat rotateX, GLfloat rotateY, GLfloat rotateZ, vec2 scaling, vec2 drawPos, vec2 drawSize);
	void renderText(string text, vec2 position, float rotation, float scaling, vec3 color);
	void renderMixColor(Texture2D* texture, vec3 color, vec3 position, vec2 size, GLfloat rotateX, GLfloat rotateY, GLfloat rotateZ, vec2 scaling, MODE mode);

private:
	struct Font {
		GLuint textureID;
		vec2 size, bearing;
		GLuint advance;
	};
#define MODESIZE 4
	Shader* shader2D;
	Shader* shaderFont;
	Shader* shaderMixColor;
	GLuint VAO[MODESIZE], VBO[MODESIZE];
	float leftTopVertex[30];
	map<GLchar, Font> fonts;

	void renderUI(Texture2D* texture, vec2 position, float rotation, vec2 size, vec2 scaling);
};
