#pragma once
#include "GameObject.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Camera.h"
#include "Widget.h"
using namespace std;

class SceneBase : public GameObject {
public:
	SceneBase(int width, int height);
	SceneBase(const SceneBase& A);
	virtual ~SceneBase();
	virtual void build();
	virtual void start() override;
	void render() override;
	Camera* getMainCamera();
	virtual void mouseCallback(GLFWwindow* window, int button, int action, int mods);
	virtual void cursorPosCallback(GLFWwindow* window, double xpos, double ypos);
	virtual void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void addObject(GameObject* object);
	GameObject* addObject(string objectName);
	void removeObject(GameObject* object);
	virtual void changeNew();
	virtual void changeBack();

protected:
	const int screenWidth, screenHeight;
	Camera* mainCamera;
	vector<Widget*> widgetList;
	void getWidgetList();
	void getWidgetList(GameObject* object);
};

