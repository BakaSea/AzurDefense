#pragma once
#include <string>
#include <map>
#include <vector>
#include <irrKlang/irrKlang.h>
#include "Texture2D.h"
#include "MapManager.h"
#include "UserData.h"
using namespace std;
using namespace irrklang;

class ResourceManager {
public:
	const string resourcePath;
	ResourceManager();
	~ResourceManager();
	void registerTexture(string name);
	void registerTexture(string name, string animate, int frames);
	Texture2D* getTexture(string name);
	Texture2D* getTexture(string name, string animate, int frame);
	void registerGameMap();
	void readUserData();
	void writeUserData();
	void initUserData();
	UserData* getUserData();
	MapManager* getMapManager();
	void registerSound(string name);
	ISoundSource* getSound(string name);

private:
	map<string, vector<Texture2D>> texture2DMap;
	map<string, ISoundSource*> soundMap;
	MapManager* mapManager;
	UserData userData;
	string combineName(string name, string animate);
};
