#include "Shader.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <fstream>
#include <sstream>
#include <iostream>
#include "DebugHelper.h"
using namespace std;
using namespace glm;

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath) {
	ifstream vsFile(vertexShaderPath), fsFile(fragmentShaderPath);
	if (!vsFile.is_open() || !fsFile.is_open()) {
		DebugHelper::logError("Cannot read shader files!");
		shaderID = -1;
	} else {
		stringstream vsStream, fsStream;
		vsStream << vsFile.rdbuf();
		fsStream << fsFile.rdbuf();
		vsFile.close();
		fsFile.close();
		string vertexCode = vsStream.str();
		string fragmentCode = fsStream.str();
		const char* vsCode = vertexCode.c_str();
		const char* fsCode = fragmentCode.c_str();

		GLint success;
		GLchar infoLog[512];
		GLuint vertexShader, fragmentShader;

		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vsCode, NULL);
		glCompileShader(vertexShader);
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			DebugHelper::logError(infoLog);
		}

		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fsCode, NULL);
		glCompileShader(fragmentShader);
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
			DebugHelper::logError(infoLog);
		}

		shaderID = glCreateProgram();
		glAttachShader(shaderID, vertexShader);
		glAttachShader(shaderID, fragmentShader);
		glLinkProgram(shaderID);
		glGetShaderiv(shaderID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
			DebugHelper::logError(infoLog);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
}

void Shader::use() {
	glUseProgram(shaderID);
}

void Shader::setMatrix4(string uniform, mat4 matrix) {
	GLuint loc = glGetUniformLocation(shaderID, uniform.c_str());
	glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::set3Float(string uniform, float v0, float v1, float v2) {
	GLuint loc = glGetUniformLocation(shaderID, uniform.c_str());
	glUniform3f(loc, v0, v1, v2);
}
