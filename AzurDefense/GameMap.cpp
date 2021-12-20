#include "GameMap.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include "DebugHelper.h"

using json = nlohmann::json;

GameMap::GameMap() {
	row = column = energy = hp = 0;
}

GameMap::GameMap(const char* mapPath) {
	ifstream mapFile(mapPath);
	if (!mapFile.is_open()) {
		DebugHelper::logError("Cannot read the map file!");
		row = column = energy = hp = 0;
	} else {
		json js;
		mapFile >> js;
		mapFile.close();
		row = js["row"];
		column = js["column"];
		energy = js["energy"];
		hp = js["hp"];
		seaType = js["seaType"];
		platform.resize(row);
		for (auto& line : platform) {
			line.resize(column);
		}
		for (int i = 0; i < row; ++i) {
			string line = js["map"][i];
			for (int j = 0; j < column; ++j) {
				switch (line[j]) {
				case '.': platform[i][j] = NORMAL; break;
				case '#': platform[i][j] = OBSTACLE; break;
				case 's': platform[i][j] = START; break;
				case 'e': platform[i][j] = END; break;
				case '$': platform[i][j] = SHORT; break;
				case '&': platform[i][j] = LONG; break;
				}
			}
		}
		int routeSize = (int)js["route"].size();
		routeList.resize(routeSize);
		for (int i = 0; i < routeSize; ++i) {
			int length = (int)js["route"][i].size();
			routeList[i].resize(length);
			for (int j = 0; j < length; ++j) {
				routeList[i][j].x = js["route"][i][j].at("x");
				routeList[i][j].y = js["route"][i][j].at("y");
			}
		}
		int enemySize = (int)js["enemy"].size();
		enemyList.resize(enemySize);
		for (int i = 0; i < enemySize; ++i) {
			enemyList[i].name = js["enemy"][i].at("name");
			enemyList[i].route = js["enemy"][i].at("route");
			enemyList[i].time = js["enemy"][i].at("time");
		}
		sort(enemyList.begin(), enemyList.end(), [](Enemy& A, Enemy& B) -> bool {
			return A.time < B.time;
			});
		int aircraftSize = (int)js["aircraft"].size();
		aircraftList.resize(aircraftSize);
		for (int i = 0; i < aircraftSize; ++i) {
			aircraftList[i].name = js["aircraft"][i].at("name");
			aircraftList[i].time = js["aircraft"][i].at("time");
			aircraftList[i].atk = js["aircraft"][i].at("atk");
			aircraftList[i].airDef = js["aircraft"][i].at("airDef");
			aircraftList[i].hp = js["aircraft"][i].at("hp");
			aircraftList[i].location.x = js["aircraft"][i].at("location")[0];
			aircraftList[i].location.y = js["aircraft"][i].at("location")[1];
			aircraftList[i].front.x = js["aircraft"][i].at("front")[0];
			aircraftList[i].front.y = js["aircraft"][i].at("front")[1];
			aircraftList[i].bellicose = js["aircraft"][i].at("bellicose");
		}
		sort(aircraftList.begin(), aircraftList.end(), [](Aircraft& A, Aircraft& B) -> bool {
			return A.time < B.time;
			});
		reward = js["reward"];
	}
}

GameMap::~GameMap() {
	row = column = 0;
	platform.clear();
	enemyList.clear();
}

int GameMap::getRow() {
	return row;
}

int GameMap::getColumn() {
	return column;
}

int GameMap::getEnergy() {
	return energy;
}

int GameMap::getHp() {
	return hp;
}

string GameMap::getSeaType() {
	return seaType;
}

GameMap::TYPE GameMap::getPlatformType(vec2 location) {
	return getPlatformType(round(location.x), round(location.y));
}

GameMap::TYPE GameMap::getPlatformType(int x, int y) {
	if (0 <= x && x < row && 0 <= y && y < column) {
		return platform[x][y];
	} else {
		return UNKNOWN;
	}
}

int GameMap::getEnemySize() {
	return enemyList.size();
}

GameMap::Enemy GameMap::getEnemy(int index) {
	return enemyList[index];
}

int GameMap::getAircraftSize() {
	return aircraftList.size();
}

GameMap::Aircraft GameMap::getAircraft(int index) {
	return aircraftList[index];
}

int GameMap::getRouteListSize() {
	return routeList.size();
}

int GameMap::getRouteSize(int id) {
	return routeList[id].size();
}

vec2 GameMap::getRouteLocation(int id, int index) {
	return routeList[id][index];
}

bool GameMap::isEnd(vec2 location) {
	return isEnd(round(location.x), round(location.y));
}

bool GameMap::isEnd(int x, int y) {
	return platform[x][y] == END;
}

string GameMap::getReward() {
	return reward;
}
