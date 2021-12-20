#pragma once
#include <vector>
#include "SceneBase.h"
using namespace std;

class SceneController {
public:
	SceneController(SceneBase* scene);
	~SceneController();
	SceneBase* getCurrentScene();
	void changeNewScene(SceneBase* scene);
	void changePrevScene();
private:
	vector<SceneBase*> sceneList;
};