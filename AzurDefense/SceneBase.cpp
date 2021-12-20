#include "SceneBase.h"
#include "Camera.h"
#include "Game.h"
#include <algorithm>

SceneBase::SceneBase(int width, int height) : screenWidth(width), screenHeight(height) {
	mainCamera = NULL;
}

SceneBase::SceneBase(const SceneBase& A) : screenWidth(A.screenWidth), screenHeight(A.screenHeight) {
	mainCamera = new Camera(*A.mainCamera);
}

SceneBase::~SceneBase() {
	delete mainCamera;
	mainCamera = NULL;
	Game::getInstance()->getSoundEngine()->stopAllSounds();
}

void SceneBase::build() {

}

void SceneBase::start() {
	build();
	GameObject::start();
}

void SceneBase::render() {
	renderLowerChild();
	renderUpperChild();
}

Camera* SceneBase::getMainCamera() {
	return mainCamera;
}

void SceneBase::mouseCallback(GLFWwindow* window, int button, int action, int mods) {

}

void SceneBase::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {

}

void SceneBase::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

}

void SceneBase::addObject(GameObject* object) {
	addChild(object);
}

GameObject* SceneBase::addObject(string objectName) {
	GameObject* object = Game::getInstance()->getRegistration()->getGameObject(objectName);
	addObject(object);
	return object;
}

void SceneBase::removeObject(GameObject* object) {
	removeChild(object);
}

void SceneBase::changeNew() {

}

void SceneBase::changeBack() {

}

void SceneBase::getWidgetList() {
	widgetList.clear();
	getWidgetList(this);
	sort(widgetList.begin(), widgetList.end(), [](Widget* A, Widget* B)->int {
		return A->getLayer() > B->getLayer();
		});
}

void SceneBase::getWidgetList(GameObject* object) {
	auto children = object->getChildList();
	for (GameObject* child : children) {
		if (child != nullptr) {
			Widget* widget = dynamic_cast<Widget*>(child);
			if (widget != nullptr) {
				widgetList.emplace_back(widget);
			}
			getWidgetList(child);
		}
	}
}
