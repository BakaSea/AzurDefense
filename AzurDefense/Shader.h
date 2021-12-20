#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
using namespace std;
using namespace glm;

class Shader {
public:
	Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
	void use();
	void setMatrix4(string uniform, mat4 matrix);
	void set3Float(string uniform, float v0, float v1, float v2);
private:
	GLuint shaderID;
};
