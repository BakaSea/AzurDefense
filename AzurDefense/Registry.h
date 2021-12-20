#pragma once
#include "GameObject.h"
#include <map>
using namespace std;

class Registry {
public:
	Registry();
	Registry(const Registry& A);
	~Registry();
	GameObject* getGameObject(string name);
	void init();
	int getRegistrySize();
	int getCurrentRegistry();

private:
	int currentRegistry;
	vector<GameObject*> objects;
	vector<string> widgets;
	vector<string> sounds;
	map<string, GameObject*> objectList;
	void registerGameObject(GameObject* obj);
	void registerTexture(string name);
	void registerGameMap();
	void registerSound(string name);
};
