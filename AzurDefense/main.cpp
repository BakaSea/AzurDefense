#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Game.h"
#include "DebugHelper.h"
using namespace std;

bool DebugHelper::debug = false;
int DebugHelper::count = 0;

int WinMain() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	Game::getInstance()->run();
	return 0;
}