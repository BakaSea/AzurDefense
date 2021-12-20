#include "SceneController.h"

SceneController::SceneController(SceneBase* scene) {
	sceneList.emplace_back(scene);
	scene->start();
}

SceneController::~SceneController() {
	for (SceneBase*& scene : sceneList) {
		delete scene;
		scene = nullptr;
	}
	sceneList.clear();
}

SceneBase* SceneController::getCurrentScene() {
	return sceneList.back();
}

void SceneController::changeNewScene(SceneBase* scene) {
	getCurrentScene()->changeNew();
	sceneList.emplace_back(scene);
	scene->start();
}

void SceneController::changePrevScene() {
	delete sceneList.back();
	sceneList.pop_back();
	getCurrentScene()->changeBack();
}
