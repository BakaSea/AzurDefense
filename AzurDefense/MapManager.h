#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include "GameMap.h"
using namespace std;

class MapManager {
public:
	MapManager();
	MapManager(const char* managerPath, const char* mapPath);
	~MapManager();
	GameMap* getGameMap(pair<int, int> mapID);
	vec2 getPosition(pair<int, int> mapID);
	int getChapterSize();
	int getMapSize(int chapter);
	pair<int, int> getNextMapID(pair<int, int> mapID);

private:
	struct ITEM {
		GameMap* gm;
		vec2 position;
	};
	vector<vector<ITEM>> mapList;
};