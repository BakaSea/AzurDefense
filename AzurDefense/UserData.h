#pragma once
#include <set>
#include <string>
#include <vector>
using namespace std;

class UserData {
public:
	UserData();
	void read(const char* dataPath);
	void write(const char* dataPath);
	void init(const char* dataPath);
	vector<string> getShipList();
	void addShip(string ship);
	bool isMapClear(pair<int, int> mapID);
	void clearMap(pair<int, int> mapID);
	bool isMapReach(pair<int, int> mapID);
	bool containShip(string ship);
	bool isFirstGame();

private:
	bool reach, firstGame;
	pair<int, int> reachID;
	set<string> shipList;
};