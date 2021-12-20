#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <string>
using namespace std;
using namespace glm;

class GameMap {
public:
	enum TYPE {
		NORMAL,
		OBSTACLE,
		START,
		END,
		SHORT,
		LONG,
		UNKNOWN
	};
	struct Enemy {
		string name;
		int time;
		int route;
	};
	struct Aircraft {
		string name;
		int time, atk, airDef, hp;
		vec2 location;
		vec2 front;
		bool bellicose;
	};
	GameMap();
	GameMap(const char* mapPath);
	~GameMap();
	int getRow();
	int getColumn();
	int getEnergy();
	int getHp();
	string getSeaType();
	TYPE getPlatformType(vec2 location);
	TYPE getPlatformType(int x, int y);
	int getEnemySize();
	Enemy getEnemy(int index);
	int getAircraftSize();
	Aircraft getAircraft(int index);
	int getRouteListSize();
	int getRouteSize(int id);
	vec2 getRouteLocation(int id, int index);
	bool isEnd(vec2 location);
	bool isEnd(int x, int y);
	string getReward();

private:
	int row, column, energy, hp;
	string seaType, reward;
	vector<vector<TYPE>> platform;
	vector<vector<vec2>> routeList;
	vector<Enemy> enemyList;
	vector<Aircraft> aircraftList;
};