#include "ResourceManager.h"
#include <string>
#include "DebugHelper.h"
#include "Game.h"
using namespace std;

ResourceManager::ResourceManager() : resourcePath("") {
	userData = UserData();
	mapManager = nullptr;
}

ResourceManager::~ResourceManager() {
	for (auto obj : texture2DMap) {
		obj.second.clear();
	}
	texture2DMap.clear();
	delete mapManager;
	mapManager = nullptr;
	soundMap.clear();
}

void ResourceManager::registerTexture(string name) {
	Texture2D texture = Texture2D((resourcePath + "Textures/" + name + ".png").c_str());
	texture2DMap[name] = vector<Texture2D>(1, texture);
}

void ResourceManager::registerTexture(string name, string animate, int frames) {
	name = combineName(name, animate);
	texture2DMap[name] = vector<Texture2D>(frames);
	for (int i = 0; i < frames; ++i) {
		texture2DMap[name][i] = Texture2D((resourcePath + "Textures/" + name + "_" + to_string(i) + ".png").c_str());
	}
}

Texture2D* ResourceManager::getTexture(string name) {
	auto result = texture2DMap.find(name);
	if (result == texture2DMap.end()) {
		DebugHelper::logError("Failed to get texture for " + name);
		return nullptr;
	} else return &result->second[0];
}

Texture2D* ResourceManager::getTexture(string name, string animate, int frame) {
	name = combineName(name, animate);
	auto result = texture2DMap.find(name);
	if (result == texture2DMap.end()) {
		DebugHelper::logError("Failed to get texture for " + name);
		return nullptr;
	} else return &result->second[frame];
}

void ResourceManager::registerGameMap() {
	mapManager = new MapManager((resourcePath + "Maps/map.json").c_str(), (resourcePath + "Maps/").c_str());
}

void ResourceManager::readUserData() {
	userData.read((resourcePath + "UserData.json").c_str());
}

void ResourceManager::writeUserData() {
	userData.write((resourcePath + "UserData.json").c_str());
}

void ResourceManager::initUserData() {
	userData.init((resourcePath + "UserData.json").c_str());
}

UserData* ResourceManager::getUserData() {
	return &userData;
}

MapManager* ResourceManager::getMapManager() {
	return mapManager;
}

void ResourceManager::registerSound(string name) {
	soundMap[name] = Game::getInstance()->getSoundEngine()->addSoundSourceFromFile((resourcePath + "Sounds/" + name + ".ogg").c_str());
}

ISoundSource* ResourceManager::getSound(string name) {
	auto result = soundMap.find(name);
	if (result == soundMap.end()) {
		DebugHelper::logError("Failed to get sound for " + name);
		return nullptr;
	} else return result->second;
}

string ResourceManager::combineName(string name, string animate) {
	return name + "/" + animate;
}
