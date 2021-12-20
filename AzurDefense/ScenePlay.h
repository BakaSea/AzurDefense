#pragma once
#include "SceneBase.h"
#include <map>
#include "GameMap.h"
#include "Ship.h"
#include "Siren.h"
#include "AirCraft.h"
#include "Text.h"
#include "Picture.h"
#include "ButtonSelectCard.h"
#include "ButtonFormation.h"
#include "ButtonCombat.h"
#include "BarHp.h"

class ScenePlay : public SceneBase {
public:
	enum LAYER {
		BACKGROUND = 0,
		PLATFORM = 10,
		NAVIGATION = 25,
		CHARACTER = 50,
		UIBG = 100,
		UI = 101,
		DRAG = 200,
		UIRESULT = 300
	};
	ScenePlay(pair<int, int> mapID, int width, int height);
	~ScenePlay();
	void build() override;
	void start() override;
	void update() override;
	void mouseCallback(GLFWwindow* window, int button, int action, int mods) override;
	void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) override;
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) override;
	void addCharacter(vec2 location, Character* charac);
	void addCharacter(int x, int y, Character* charac);
	void removeCharacter(vec2 location, Character* charac);
	void removeCharacter(int x, int y, Character* charac);
	vector<Siren*> getSirenList(vec2 location);
	vector<Siren*> getSirenList(int x, int y);
	vector<AirCraft*> getAirCraftList(vec2 location);
	vector<AirCraft*> getAirCraftList(int x, int y);
	Ship* getShip(vec2 location);
	Ship* getShip(int x, int y);
	GameMap* getGameMap();
	vec3 getPositionByLocation(vec2 location);
	vec3 getPositionByLocation(int x, int y);
	void changeLocation(Character* charac, int oldX, int oldY, int newX, int newY);
	void changeLocation(Character* charac, vec2 oldLocation, vec2 newLocation);
	int getEnergy();
	void increaseEnergy(int inc);
	void decreaseEnergy(int dec);
	void increaseEnemyDown();
	bool isRunning();
	void run();
	void stop();
	void unstop();
	vector<GameObject*> getCollision(GameObject* object, float radius);
	bool blockCharacter(vec2 location, Character* charac);
	bool blockCharacter(int x, int y, Character* charac);
	bool unblockCharacter(vec2 location, Character* charac);
	bool unblockCharacter(int x, int y, Character* charac);
	int getHp();
	int getMaxHp();
	void getDamge(int damage);
	bool addBtnSelectCard(string ship);
	bool removeBtnSelectCard(string ship);
	bool isLegalLocation(vec2 location);
	bool isLegalLocation(int x, int y);

private:
	struct VECCMP {
		bool operator() (const vec2& A, const vec2& B) const {
			if (fabs(A.x-B.x) > 1e-5f) return B.x-A.x > 1e-5f;
			return B.y-A.y > 1e-5f;
		}
	};

	struct SLOT {
		vector<Siren*> sirenList;
		set<Siren*> blockList;
		vector<AirCraft*> airCraftList;
		Ship* ship;
		SLOT() {
			sirenList.clear();
			blockList.clear();
			airCraftList.clear();
			ship = nullptr;
		}
	};

	bool running, prevRunning;
	int dragging, selecting, enemyIndex, aircraftIndex, energy, enemyDown, countTime, hp, maxHp;
	Ship* dragShip;
	ButtonSelectCard* dragBtn;
	
	pair<int, int> mapID;

	vector<vector<SLOT>> slotList;
	map<vec2, vec3, VECCMP> locationPosition;

	Text* textEnergy;
	ButtonFormation* btnFormation;
	ButtonCombat* btnCombat;
	vector<ButtonSelectCard*> btnSelectCardList;
	BarHp* barHp;

	void succeed();
	void fail();
	bool isPlaced(vec2 location);
	bool isPlaced(int x, int y);
	void updateBtnSelectCardList();
	void moveCamera(vec3 distance);
	int getBarHpBossCount();
	void moveBarHpBoss();
};