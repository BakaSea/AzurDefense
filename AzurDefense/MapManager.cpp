#include "MapManager.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include "DebugHelper.h"

using json = nlohmann::json;

MapManager::MapManager() {
	mapList.clear();
}

MapManager::MapManager(const char* managerPath, const char* mapPath) {
	ifstream file(managerPath);
	if (!file.is_open()) {
		DebugHelper::logError("Cannot open map file!");
	} else {
		json js;
		file >> js;
		file.close();
		int chapterSize = (int)js.size();
		mapList.resize(chapterSize);
		for (int i = 0; i < chapterSize; ++i) {
			int mapSize = (int)js[i].size();
			mapList[i].resize(mapSize);
			for (int j = 0; j < mapSize; ++j) {
				DebugHelper::logInfo("Register map " + to_string(i + 1) + "-" + to_string(j + 1));
				mapList[i][j].gm = new GameMap((string(mapPath) + to_string(i + 1) + "-" + to_string(j + 1) + ".json").c_str());
				mapList[i][j].position.x = js[i][j]["x"];
				mapList[i][j].position.y = js[i][j]["y"];
			}
		}
	}
}

MapManager::~MapManager() {
	for (auto chapter : mapList) {
		for (auto& item : chapter) {
			delete item.gm;
			item.gm = nullptr;
		}
	}
	mapList.clear();
}

GameMap* MapManager::getGameMap(pair<int, int> mapID) {
	return mapList[mapID.first - 1][mapID.second - 1].gm;
}

vec2 MapManager::getPosition(pair<int, int> mapID) {
	return mapList[mapID.first - 1][mapID.second - 1].position;
}

int MapManager::getChapterSize() {
	return mapList.size();
}

int MapManager::getMapSize(int chapter) {
	return mapList[chapter - 1].size();
}

pair<int, int> MapManager::getNextMapID(pair<int, int> mapID) {
	int x = mapID.first - 1, y = mapID.second - 1;
	y++;
	if (y == mapList[x].size()) {
		x++;
		y = 0;
	}
	if (x == mapList.size()) {
		return make_pair(-1, -1);
	}
	return make_pair(x + 1, y + 1);
}
