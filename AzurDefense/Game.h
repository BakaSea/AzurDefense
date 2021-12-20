#pragma once
#pragma comment(lib, "irrKlang.lib")
#include <string>
#include <irrKlang/irrKlang.h>
#include "Registry.h"
#include "Renderer2D.h"
#include "ResourceManager.h"
#include "SceneController.h"
using namespace std;
using namespace irrklang;

class Game {
public:
	const int screenWidth, screenHeight;
	const string title;

	Game();
	~Game();
	static Game* getInstance();
	static void mouseCallback(GLFWwindow* window, int button, int action, int mods);
	static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void run();
	void stop();

	ResourceManager* getResourceManager();
	Registry* getRegistration();
	Renderer2D* getRenderer2D();
	SceneController* getSceneController();
	ISoundEngine* getSoundEngine();
	int getDeltaTime();
	int getTotalTime();

private:
	static Game instance;
	ResourceManager* resourceManager;
	Registry* registration;
	Renderer2D* renderer2D;
	SceneController* sceneController;
	ISoundEngine* soundEngine;
	int deltaTime, totalTime;
	bool signalStop;
};
