#include "Renderer2D.h"
#include "ft2build.h"
#include FT_FREETYPE_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Texture2D.h"
#include "DebugHelper.h"
#include "Game.h"
#include "MathHelper.h"
using namespace glm;

Renderer2D::Renderer2D() {
	shader2D = new Shader((Game::getInstance()->getResourceManager()->resourcePath + "Shaders/Shader2D.vs").c_str(),
		(Game::getInstance()->getResourceManager()->resourcePath + "Shaders/Shader2D.fs").c_str());
	shaderFont = new Shader((Game::getInstance()->getResourceManager()->resourcePath + "Shaders/Shader2D.vs").c_str(),
		(Game::getInstance()->getResourceManager()->resourcePath + "Shaders/ShaderFont.fs").c_str());
	shaderMixColor = new Shader((Game::getInstance()->getResourceManager()->resourcePath + "Shaders/Shader2D.vs").c_str(),
		(Game::getInstance()->getResourceManager()->resourcePath + "Shaders/ShaderMixColor.fs").c_str());
	glGenVertexArrays(MODESIZE, VAO);
	glGenBuffers(MODESIZE, VBO);
	
	float middleVertex[] = {
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f
	};
	glBindBuffer(GL_ARRAY_BUFFER, VBO[MIDDLE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(middleVertex), middleVertex, GL_DYNAMIC_DRAW);
	glBindVertexArray(VAO[MIDDLE]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	float bottomVertex[] = {
		-0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.0f, 0.0f, 1.0f, 0.0f
	};
	glBindBuffer(GL_ARRAY_BUFFER, VBO[BOTTOM]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(bottomVertex), bottomVertex, GL_DYNAMIC_DRAW);
	glBindVertexArray(VAO[BOTTOM]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	leftTopVertex[0] = 0.0f; leftTopVertex[1] = 0.0f; leftTopVertex[2] = 0.0f; leftTopVertex[3] = 0.0f; leftTopVertex[4] = 1.0f; //Left top
	leftTopVertex[5] = 1.0f; leftTopVertex[6] = -1.0f; leftTopVertex[7] = 0.0f; leftTopVertex[8] = 1.0f; leftTopVertex[9] = 0.0f; //Right bottom
	leftTopVertex[10] = 0.0f; leftTopVertex[11] = -1.0f; leftTopVertex[12] = 0.0f; leftTopVertex[13] = 0.0f; leftTopVertex[14] = 0.0f; //Left bottom
	leftTopVertex[15] = 0.0f; leftTopVertex[16] = 0.0f; leftTopVertex[17] = 0.0f; leftTopVertex[18] = 0.0f; leftTopVertex[19] = 1.0f; //Left top
	leftTopVertex[20] = 1.0f; leftTopVertex[21] = 0.0f; leftTopVertex[22] = 0.0f; leftTopVertex[23] = 1.0f; leftTopVertex[24] = 1.0f; //Right top
	leftTopVertex[25] = 1.0f; leftTopVertex[26] = -1.0f; leftTopVertex[27] = 0.0f; leftTopVertex[28] = 1.0f; leftTopVertex[29] = 0.0f; //Right bottom
	glBindBuffer(GL_ARRAY_BUFFER, VBO[LEFTTOP]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(leftTopVertex), leftTopVertex, GL_DYNAMIC_DRAW);
	glBindVertexArray(VAO[LEFTTOP]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Render font preparation
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		DebugHelper::logError("Cannot init FreeType library!");
	}
	FT_Face face;
	if (FT_New_Face(ft, (Game::getInstance()->getResourceManager()->resourcePath + "Fonts/arial.ttf").c_str(), 0, &face)) {
		DebugHelper::logError("Failed to load font!");
	}
	FT_Set_Pixel_Sizes(face, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	for (GLubyte c = 0; c < 128; ++c) {
		if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
			DebugHelper::logError("Failed to load Glyph!");
		}
		Font font;
		glGenTextures(1, &font.textureID);
		glBindTexture(GL_TEXTURE_2D, font.textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		font.size = vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
		font.bearing = vec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
		font.advance = face->glyph->advance.x;
		fonts[c] = font;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	FT_Done_Face(face);
	FT_Done_FreeType(ft);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[FONT]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 5, NULL, GL_DYNAMIC_DRAW);
	glBindVertexArray(VAO[FONT]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Renderer2D::Renderer2D(const Renderer2D& A) {
	shader2D = new Shader(*A.shader2D);
	shaderFont = new Shader(*A.shaderFont);
	memcpy(VAO, A.VAO, sizeof(A.VAO));
	memcpy(VBO, A.VBO, sizeof(A.VBO));
	memcpy(leftTopVertex, A.leftTopVertex, sizeof(leftTopVertex));
	fonts = A.fonts;
}

Renderer2D::~Renderer2D() {
	glDeleteVertexArrays(MODESIZE, VAO);
	glDeleteBuffers(MODESIZE, VBO);
	fonts.clear();
	delete shader2D;
	shader2D = nullptr;
	delete shaderFont;
	shaderFont = nullptr;
	delete shaderMixColor;
	shaderMixColor = nullptr;
}

void Renderer2D::render(Texture2D *texture, vec3 position, vec2 size, GLfloat rotateX, GLfloat rotateY, GLfloat rotateZ, vec2 scaling, MODE mode) {
	shader2D->use();
	mat4 model = mat4(1.0f);
	mat4 view = mat4(1.0f);
	mat4 projection = mat4(1.0f);
	
	model = MathHelper::getModelMatrix(position, rotateX, rotateY, rotateZ, size, scaling);
	
	Camera* camera = Game::getInstance()->getSceneController()->getCurrentScene()->getMainCamera();
	if (camera == NULL) {
		DebugHelper::logError("No camera!");
		return;
	}
	view = camera->getViewMatrix();
	projection = camera->getProjectionMatrix();
	
	shader2D->setMatrix4("model", model);
	shader2D->setMatrix4("view", view);
	shader2D->setMatrix4("projection", projection);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	texture->bindTexture();

	glBindVertexArray(VAO[mode]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glDisable(GL_BLEND);
}

void Renderer2D::renderUI(Texture2D* texture, vec2 position, float rotation, vec2 size, vec2 scaling, vec2 drawPos, vec2 drawSize) {
	vec2 textureSize = texture->getSize();
	drawPos.y = textureSize.y - drawPos.y;
	vec2 leftTop = vec2(drawPos.x / textureSize.x, drawPos.y / textureSize.y);
	vec2 leftBottom = vec2(drawPos.x / textureSize.x, (drawPos.y - drawSize.y) / textureSize.y);
	vec2 rightTop = vec2((drawPos.x + drawSize.x) / textureSize.x, drawPos.y / textureSize.y);
	vec2 rightBottom = vec2((drawPos.x + drawSize.x) / textureSize.x, (drawPos.y - drawSize.y) / textureSize.y);
	leftTopVertex[3] = leftTop.x; leftTopVertex[4] = leftTop.y;
	leftTopVertex[8] = rightBottom.x; leftTopVertex[9] = rightBottom.y;
	leftTopVertex[13] = leftBottom.x; leftTopVertex[14] = leftBottom.y;
	leftTopVertex[18] = leftTop.x; leftTopVertex[19] = leftTop.y;
	leftTopVertex[23] = rightTop.x; leftTopVertex[24] = rightTop.y;
	leftTopVertex[28] = rightBottom.x; leftTopVertex[29] = rightBottom.y;
	glBindBuffer(GL_ARRAY_BUFFER, VBO[LEFTTOP]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(leftTopVertex), leftTopVertex);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	renderUI(texture, position, rotation, size, scaling);
}

void Renderer2D::renderUI3D(Texture2D* texture, vec3 position, vec2 size, GLfloat rotateX, GLfloat rotateY, GLfloat rotateZ, vec2 scaling, vec2 drawPos, vec2 drawSize) {
	vec2 textureSize = texture->getSize();
	drawPos.y = textureSize.y - drawPos.y;
	vec2 leftTop = vec2(drawPos.x / textureSize.x, drawPos.y / textureSize.y);
	vec2 leftBottom = vec2(drawPos.x / textureSize.x, (drawPos.y - drawSize.y) / textureSize.y);
	vec2 rightTop = vec2((drawPos.x + drawSize.x) / textureSize.x, drawPos.y / textureSize.y);
	vec2 rightBottom = vec2((drawPos.x + drawSize.x) / textureSize.x, (drawPos.y - drawSize.y) / textureSize.y);
	leftTopVertex[3] = leftTop.x; leftTopVertex[4] = leftTop.y;
	leftTopVertex[8] = rightBottom.x; leftTopVertex[9] = rightBottom.y;
	leftTopVertex[13] = leftBottom.x; leftTopVertex[14] = leftBottom.y;
	leftTopVertex[18] = leftTop.x; leftTopVertex[19] = leftTop.y;
	leftTopVertex[23] = rightTop.x; leftTopVertex[24] = rightTop.y;
	leftTopVertex[28] = rightBottom.x; leftTopVertex[29] = rightBottom.y;
	glBindBuffer(GL_ARRAY_BUFFER, VBO[LEFTTOP]);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(leftTopVertex), leftTopVertex);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	render(texture, position, size, rotateX, rotateY, rotateZ, scaling, LEFTTOP);
}

void Renderer2D::renderText(string text, vec2 position, float rotation, float scaling, vec3 color) {
	shaderFont->use();
	shaderFont->set3Float("textColor", color.x, color.y, color.z);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (char c : text) {
		Font ch = fonts[c];
		GLfloat x = ch.bearing.x * scaling;
		GLfloat y = -(ch.size.y - ch.bearing.y) * scaling;
		GLfloat w = ch.size.x * scaling;
		GLfloat h = ch.size.y * scaling;
		GLfloat fontVertex[] = {
			x, y + h, 0.0f, 0.0f, 0.0f,
			x, y, 0.0f, 0.0f, 1.0f,
			x + w, y, 0.0f, 1.0f, 1.0f,
			x, y + h, 0.0f, 0.0f, 0.0f,
			x + w, y, 0.0f, 1.0f, 1.0f,
			x + w, y + h, 0.0f, 1.0f, 0.0f
		};
		glBindBuffer(GL_ARRAY_BUFFER, VBO[FONT]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(fontVertex), fontVertex);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		mat4 model = mat4(1.0f);
		mat4 view = mat4(1.0f);
		mat4 projection = mat4(1.0f);

		model = MathHelper::getModelMatrix(vec3(position, 0.0f), 0.0f, 0.0f, rotation, vec2(1.0f, 1.0f), vec2(1.0f, 1.0f));

		Camera* camera = Game::getInstance()->getSceneController()->getCurrentScene()->getMainCamera();
		if (camera == NULL) {
			DebugHelper::logError("No camera!");
			return;
		}

		projection = camera->getUIMatrix();

		shaderFont->setMatrix4("model", model);
		shaderFont->setMatrix4("view", view);
		shaderFont->setMatrix4("projection", projection);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, ch.textureID);
		glBindVertexArray(VAO[FONT]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		position.x += (ch.advance >> 6) * scaling;
	}
	glDisable(GL_BLEND);
}

void Renderer2D::renderMixColor(Texture2D* texture, vec3 color, vec3 position, vec2 size, GLfloat rotateX, GLfloat rotateY, GLfloat rotateZ, vec2 scaling, MODE mode) {
	shaderMixColor->use();
	mat4 model = mat4(1.0f);
	mat4 view = mat4(1.0f);
	mat4 projection = mat4(1.0f);

	model = MathHelper::getModelMatrix(position, rotateX, rotateY, rotateZ, size, scaling);

	Camera* camera = Game::getInstance()->getSceneController()->getCurrentScene()->getMainCamera();
	if (camera == NULL) {
		DebugHelper::logError("No camera!");
		return;
	}
	view = camera->getViewMatrix();
	projection = camera->getProjectionMatrix();

	shaderMixColor->setMatrix4("model", model);
	shaderMixColor->setMatrix4("view", view);
	shaderMixColor->setMatrix4("projection", projection);
	shaderMixColor->set3Float("_color", color.x, color.y, color.z);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	texture->bindTexture();

	glBindVertexArray(VAO[mode]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glDisable(GL_BLEND);
}

void Renderer2D::renderUI(Texture2D* texture, vec2 position, float rotation, vec2 size, vec2 scaling) {
	shader2D->use();
	mat4 model = mat4(1.0f);
	mat4 view = mat4(1.0f);
	mat4 projection = mat4(1.0f);

	model = MathHelper::getModelMatrix(vec3(position, 0.0f), 0.0f, 0.0f, rotation, size, scaling);

	Camera* camera = Game::getInstance()->getSceneController()->getCurrentScene()->getMainCamera();
	if (camera == NULL) {
		DebugHelper::logError("No camera!");
		return;
	}

	projection = camera->getUIMatrix();

	shader2D->setMatrix4("model", model);
	shader2D->setMatrix4("view", view);
	shader2D->setMatrix4("projection", projection);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	texture->bindTexture();

	glBindVertexArray(VAO[LEFTTOP]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glDisable(GL_BLEND);
}
