#include "UserData.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include "DebugHelper.h"
#include "Game.h"

using json = nlohmann::json;

UserData::UserData() {
	reachID = make_pair(0, 0);
	reach = false;
	firstGame = false;
	shipList.clear();
}

void UserData::read(const char* dataPath) {
	reachID = make_pair(0, 0);
	shipList.clear();
	ifstream dataFile(dataPath);
	if (!dataFile.is_open()) {
		firstGame = true;
	} else {
		json js;
		dataFile >> js;
		dataFile.close();
		reach = js["reach"];
		reachID.first = js["map"][0];
		reachID.second = js["map"][1];
		int shipSize = (int)js["ship"].size();
		for (int i = 0; i < shipSize; ++i) {
			string ship = js["ship"][i];
			shipList.insert(ship);
		}
	}
}

void UserData::write(const char* dataPath) {
	json js;
	js["map"][0] = reachID.first;
	js["map"][1] = reachID.second;
	js["reach"] = reach;
	for (string ship : shipList) {
		js["ship"].emplace_back(ship);
	}
	ofstream dataFile(dataPath);
	if (!dataFile.is_open()) {
		DebugHelper::logError("Cannot open user data file!");
		return;
	} else {
		dataFile << js;
		dataFile.close();
	}
}

vector<string> UserData::getShipList() {
	vector<string> result;
	result.assign(shipList.begin(), shipList.end());
	return result;
}

void UserData::addShip(string ship) {
	shipList.insert(ship);
}

bool UserData::isMapClear(pair<int, int> mapID) {
	if (mapID.first < reachID.first) return true;
	if (mapID.first == reachID.first) {
		if (mapID.second < reachID.second) return true;
		if (mapID.second == reachID.second) return reach;
	}
	return false;
}

void UserData::clearMap(pair<int, int> mapID) {
	if ((mapID == reachID && !reach) || mapID > reachID) {
		auto nextID = Game::getInstance()->getResourceManager()->getMapManager()->getNextMapID(reachID);
		if (nextID == make_pair(-1, -1)) {
			reach = true;
		} else {
			reachID = nextID;
		}
	}
}

bool UserData::isMapReach(pair<int, int> mapID) {
	return mapID <= reachID || (isMapClear(reachID) && mapID == Game::getInstance()->getResourceManager()->getMapManager()->getNextMapID(reachID));
}

bool UserData::containShip(string ship) {
	return shipList.find(ship) != shipList.end();
}

bool UserData::isFirstGame() {
	return firstGame;
}

void UserData::init(const char* dataPath) {
	reachID = make_pair(1, 1);
	reach = false;
	firstGame = false;
	shipList.clear();
	shipList.insert("Ayanami");
	shipList.insert("Javelin");
	shipList.insert("Laffey");
	shipList.insert("Z23");
	write(dataPath);
}
