#include "Game.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <time.h>
#include <stb_image.h>
#include "DebugHelper.h"
#include "SceneLoading.h"

Game Game::instance = Game();

Game::Game() : screenWidth(1280), screenHeight(720), title("Azur Defense") {
	resourceManager = nullptr;
	registration = nullptr;
	renderer2D = nullptr;
	sceneController = nullptr;
	soundEngine = nullptr;
	deltaTime = totalTime = 0;
	signalStop = false;
}

Game::~Game() {
	delete resourceManager;
	delete registration;
	delete renderer2D;
	delete sceneController;
	resourceManager = nullptr;
	registration = nullptr;
	renderer2D = nullptr;
	sceneController = nullptr;
	soundEngine->drop();
	deltaTime = totalTime = 0;
	signalStop = false;
}

Game* Game::getInstance() {
	return &instance;
}

void Game::mouseCallback(GLFWwindow* window, int button, int action, int mods) {
	getInstance()->getSceneController()->getCurrentScene()->mouseCallback(window, button, action, mods);
}

void Game::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
	getInstance()->getSceneController()->getCurrentScene()->cursorPosCallback(window, xpos, ypos);
}

void Game::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	getInstance()->getSceneController()->getCurrentScene()->keyCallback(window, key, scancode, action, mods);
}

void Game::run() {
	srand(time(NULL));

	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, title.c_str(), NULL, NULL);
	if (window == NULL) {
		DebugHelper::logError("Failed to create GLFW window");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		DebugHelper::logError("Failed to run GLAD");
		glfwTerminate();
		return;
	}

	GLFWimage icon;
	icon.pixels = stbi_load("Textures/Icon.png", &icon.width, &icon.height, 0, STBI_rgb_alpha);
	glfwSetWindowIcon(window, 1, &icon);
	stbi_image_free(icon.pixels);

	DebugHelper::logInfo("Creating resource manager...");
	resourceManager = new ResourceManager();

	DebugHelper::logInfo("Registering...");
	registration = new Registry();
	
	DebugHelper::logInfo("Creating renderer...");
	renderer2D = new Renderer2D();
	
	DebugHelper::logInfo("Creating sound engine...");
	soundEngine = createIrrKlangDevice();
	soundEngine->setSoundVolume(0.1f);

	sceneController = new SceneController(new SceneLoading(screenWidth, screenHeight));
	totalTime = GetTickCount64();

	glfwSetMouseButtonCallback(window, mouseCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetKeyCallback(window, keyCallback);

	DebugHelper::logInfo("Show the window");
	while (!glfwWindowShouldClose(window)) {
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		int tmpTime = (int)GetTickCount64();
		deltaTime = tmpTime - totalTime;
		totalTime = tmpTime;

		sceneController->getCurrentScene()->render();
		sceneController->getCurrentScene()->update();

		glfwSwapBuffers(window);
		glfwPollEvents();

		if (signalStop) break;
	}

	glfwTerminate();
}

void Game::stop() {
	signalStop = true;
}

ResourceManager* Game::getResourceManager() {
	return resourceManager;
}

Registry* Game::getRegistration() {
	return registration;
}

Renderer2D* Game::getRenderer2D() {
	return renderer2D;
}

SceneController* Game::getSceneController() {
	return sceneController;
}

ISoundEngine* Game::getSoundEngine() {
	return soundEngine;
}

int Game::getDeltaTime() {
	return deltaTime;
}

int Game::getTotalTime() {
	return totalTime;
}