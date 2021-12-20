#include "ScenePlay.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <algorithm>
#include "DebugHelper.h"
#include "MathHelper.h"
#include "Game.h"
#include "Platform.h"
#include "ButtonSelectCard.h"
#include "Picture3D.h"
#include "ButtonSelecting.h"
#include "Siren.h"
#include "ButtonPlayStop.h"
#include "Navigation.h"
#include "Timer.h"
#include "BarHpBoss.h"
using namespace glm;

ScenePlay::ScenePlay(pair<int, int> mapID, int width, int height) : SceneBase(width, height) {
	this->mapID = mapID;
	dragging = false;
	dragShip = nullptr;
	dragBtn = nullptr;
	selecting = 0;
	countTime = 0;
	enemyIndex = aircraftIndex = 0;
	enemyDown = 0;
	running = prevRunning = false;
	energy = 0;
	hp = 0;
	maxHp = 0;
	slotList.clear();
	locationPosition.clear();
	textEnergy = nullptr;
	btnFormation = nullptr;
	btnCombat = nullptr;
	btnSelectCardList.clear();
	barHp = nullptr;
}

ScenePlay::~ScenePlay() {
	dragging = false;
	dragShip = nullptr;
	dragBtn = nullptr;
	dragBtn = nullptr;
	selecting = 0;
	countTime = 0;
	enemyIndex = aircraftIndex = 0;
	enemyDown = 0;
	running = prevRunning = false;
	mapID = make_pair(0, 0);
	energy = 0;
	hp = 0;
	maxHp = 0;
	slotList.clear();
	locationPosition.clear();
	textEnergy = nullptr;
	btnFormation = nullptr;
	btnCombat = nullptr;
	btnSelectCardList.clear();
	barHp = nullptr;
}

void ScenePlay::build() {
	mainCamera = new Camera(screenWidth, screenHeight, 90.0f, 0.1f, 50.0f);
	DebugHelper::logInfo("Playing...");

	mainCamera->setPosition(0.0f, 4.5f, 1.0f);
	mainCamera->setRotation(-80.0f, -90.0f);

	Picture* background = new Picture("Background", vec2(16.0f, 9.0f), vec2(-8.0f, 4.5f), vec2(1024.0f, 576.0f));
	background->setPosition(-8.0f, 4.5f);
	background->setLayer(BACKGROUND);
	addObject(background);

	maxHp = getGameMap()->getHp();
	hp = maxHp;

	DebugHelper::logInfo("Constructing platform...");
	int row = getGameMap()->getRow(), col = getGameMap()->getColumn();
	slotList.resize(row);
	for (auto& line : slotList) {
		line.resize(col);
	}

	int zi = -row / 2, xi = -col / 2;

	for (int z = zi; z < row + zi; ++z) {
		for (int x = xi; x < col + xi; ++x) {
			string platformName;
			switch (getGameMap()->getPlatformType(z - zi, x - xi)) {
			case GameMap::NORMAL: platformName = "Platform"; break;
			case GameMap::OBSTACLE: platformName = "PlatformObstacle"; break;
			case GameMap::START: platformName = "PlatformStart"; break;
			case GameMap::END: platformName = "PlatformEnd"; break;
			case GameMap::SHORT: platformName = "PlatformShort"; break;
			case GameMap::LONG: platformName = "PlatformLong"; break;
			}
			Platform* platform = dynamic_cast<Platform*>(addObject(platformName));
			vec2 bound = platform->getBound();
			platform->setLayer(PLATFORM);
			platform->setPosition(vec3(x + bound.x, 0.0f, z + bound.y));
			platform->setRotation(-90.0f, 0.0f, 0.0f);
			platform->setLocation(z - zi, x - xi);
			locationPosition[platform->getLocation()] = platform->getPosition();
		}
	}

	Picture3D* bgPlatform = new Picture3D("Sea" + getGameMap()->getSeaType(), vec2(col, row), vec2(0.0f, 0.0f), vec2(1024.0f, 510.0f));
	bgPlatform->setLayer(PLATFORM - 1);
	bgPlatform->setPosition(vec3(xi, 0.0f, zi));
	bgPlatform->setRotation(-90.0f, 0.0f, 0.0f);
	addObject(bgPlatform);

	Picture* bgPlayUI = new Picture("BarShips", "BGPlayUI", vec2(1.5f, 9.0f), vec2(0.0f, 0.0f), vec2(120.0f, 720.0f));
	bgPlayUI->setLayer(UIBG);
	bgPlayUI->setPosition(-8.0f, 4.5f);
	addObject(bgPlayUI);

	btnFormation = new ButtonFormation();
	btnFormation->setLayer(UI);
	btnFormation->setPosition(-6.5f, -3.5f);
	addObject(btnFormation);

	btnCombat = new ButtonCombat();
	btnCombat->setLayer(UI);
	btnCombat->setPosition(-4.0f, -3.5f);
	addObject(btnCombat);

	ButtonPlayStop* btnPlayStop = new ButtonPlayStop();
	btnPlayStop->setLayer(UI);
	btnPlayStop->setPosition(7.2f, 4.3f);
	addObject(btnPlayStop);

	addObject(new Timer(Timer::INTERVAL, 5000, true, [=]() -> void {
		for (int i = 0; i < getGameMap()->getRouteListSize(); ++i) {
			Navigation* navi = new Navigation();
			navi->setPosition(locationPosition[getGameMap()->getRouteLocation(i, 0)]);
			navi->setLayer(NAVIGATION);
			navi->setRotation(-90.0f, 0.0f, 0.0f);
			navi->setRoute(i);
			addObject(navi);
		}
	}));

	barHp = new BarHp();
	barHp->setLayer(UI);
	barHp->setScaling(vec2(5.0f, 3.0f));
	barHp->setRotation(mainCamera->getPitch(), 0.0f, 90.0f);
	barHp->setPosition(vec3(6.5f, 0.0f, 2.5f));
	addObject(barHp);
}

void ScenePlay::start() {
	SceneBase::start();
	dragging = false;
	dragShip = nullptr;
	dragBtn = nullptr;

	selecting = 0;

	running = false;
	countTime = 0;
	enemyIndex = aircraftIndex = 0;

	Game::getInstance()->getSoundEngine()->play2D(Game::getInstance()->getResourceManager()->getSound("BGMPlay"), true);
}

void ScenePlay::update() {
	SceneBase::update();
	if (running) {
		textEnergy->setText("Energy: " + to_string(energy));
		countTime += Game::getInstance()->getDeltaTime();
		if (aircraftIndex < getGameMap()->getAircraftSize()) {
			GameMap::Aircraft aircraft = getGameMap()->getAircraft(aircraftIndex);
			if (aircraft.time * 1000 <= countTime) {
				AirCraft* charac = dynamic_cast<AirCraft*>(addObject(aircraft.name));
				charac->setLayer(CHARACTER + 1);
				charac->setRotation(mainCamera->getPitch(), 0.0f, 0.0f);
				addCharacter(aircraft.location, charac);
				charac->setFront(aircraft.front);
				charac->setAttack(aircraft.atk);
				charac->setAirDef(aircraft.airDef);
				charac->setMaxHp(aircraft.hp);
				charac->setHp(aircraft.hp);
				charac->setBellicose(aircraft.bellicose);
				charac->setEnemy(true);
				aircraftIndex++;
			}
		}
		if (enemyIndex < getGameMap()->getEnemySize()) {
			GameMap::Enemy enemy = getGameMap()->getEnemy(enemyIndex);
			if (enemy.time * 1000 <= countTime) {
				Siren* charac = dynamic_cast<Siren*>(addObject(enemy.name));
				charac->setLayer(CHARACTER);
				charac->setRotation(mainCamera->getPitch(), 0.0f, 0.0f);
				charac->setStatus(Character::MOVE);
				vec2 location = getGameMap()->getRouteLocation(enemy.route, 0);
				addCharacter(location, charac);
				charac->setRoute(enemy.route);
				enemyIndex++;
			}
		} else {
			if (enemyDown == getGameMap()->getEnemySize() + getGameMap()->getAircraftSize()) {
				succeed();
			}
		}
	}
}

void ScenePlay::mouseCallback(GLFWwindow* window, int button, int action, int mods) {
	getWidgetList();
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	bool widgetFlag = false;
	for (Widget* widget : widgetList) {
		//3D...
		vec3 point(0.0f);
		if (widget->is3D()) {
			MathHelper::Line ray = mainCamera->screenToWorldLine((float)x, (float)y);
			point = MathHelper::pointLinePlane(ray, widget->getPlane());
		} else {
			point = mainCamera->screenToUIPoint((float)x, (float)y);
		}
		if (widget->inBound(point)) {
			if (widget->canClick()) {
				string widgetName = widget->getName();
				int res = widget->click(window, button, action, mods);
				widgetFlag = true;
				if (widgetName == "ButtonSelecting") {
					if (res == 0 || res == 1) {
						selecting = 2;
					} else {
						selecting = 0;
					}
					break;
				} else {
					if (widgetName == "ButtonSelectCard") {
						if (res == 1) {
							dragging = true;
							dragShip = dynamic_cast<Ship*>(childList.back());
							dragShip->setLayer(DRAG);
							dragBtn = dynamic_cast<ButtonSelectCard*>(widget);
						}
					} else if (widgetName == "ButtonCancel") {
						if (res) {
							unstop();
						}
					} else if (widgetName == "ButtonConfirmPlayStop") {
						if (res) {
							return;
						}
					}
					if (selecting == 2) {
						selecting = 1;
					}
					break;
				}
			}
			if (widget->getName() == "Picture") {
				Picture* pic = dynamic_cast<Picture*>(widget);
				if (pic->getPictureName() == "Win") {
					removeObject(pic);
					string reward = getGameMap()->getReward();
					Game::getInstance()->getResourceManager()->getUserData()->clearMap(mapID);
					if (reward.empty() || Game::getInstance()->getResourceManager()->getUserData()->containShip(reward)) {
						Game::getInstance()->getSceneController()->changePrevScene();
					} else {
						Game::getInstance()->getResourceManager()->getUserData()->addShip(reward);
						Picture* picReward = new Picture("Reward", vec2(16.0f, 9.0f), vec2(0.0f, 0.0f), vec2(1280.0f, 720.0f));
						picReward->setLayer(UIRESULT);
						picReward->setPosition(-8.0f, 4.5f);
						addObject(picReward);
						ButtonSelectCard* btn = new ButtonSelectCard(dynamic_cast<Ship*>(Game::getInstance()->getRegistration()->getGameObject(reward)));
						picReward->addChild(btn);
						btn->setLayer(1);
						btn->enableAbsolutePosition();
						btn->setPosition(-btn->getBound().x, btn->getBound().y);
					}
					Game::getInstance()->getResourceManager()->writeUserData();
					return;
				} else if (pic->getPictureName() == "Lose") {
					Game::getInstance()->getSceneController()->changePrevScene();
					return;
				} else if (pic->getPictureName() == "Reward") {
					if (action == GLFW_PRESS) {
						Game::getInstance()->getSceneController()->changePrevScene();
					}
					return;
				}
			}
		}
	}
	if (!widgetFlag) {
		if (selecting == 2) {
			selecting = 1;
		}
	}
	if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {
		if (selecting == 1) {
			for (Widget* widget : widgetList) {
				if (widget->getName() == "ButtonSelecting") {
					widget->remove();
					break;
				}
			}
			selecting = 0;
			return;
		}
	}
	if (widgetFlag) return;
	//For platform
	if (action == GLFW_PRESS) {
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			MathHelper::Line ray = mainCamera->screenToWorldLine((float)x, (float)y);
			MathHelper::Plane plane = MathHelper::Plane(0.0f, 1.0f, 0.0f, 0.0f);
			vec3 point = MathHelper::pointLinePlane(ray, plane);
			for (GameObject* obj : childList) {
				Platform* platform = dynamic_cast<Platform*>(obj);
				if (platform != nullptr) {
					if (platform->inBound(point)) {
						Ship* ship = getShip(platform->getLocation());
						if (ship != nullptr) {
							if (ship->canSelected() && ship->getStatus() != Character::DEAD) {
								ButtonSelecting* btnSelecting = new ButtonSelecting();
								ship->addChild(btnSelecting);
								btnSelecting->setLayer(-1);
								btnSelecting->setPosition(vec3(-1.5f, 0.0f, -1.5f));
								btnSelecting->enableAbsoluteScale();
								btnSelecting->enableAbsoluteRotation();
								btnSelecting->setRotation(-90.0f, 0.0f, 0.0f);
								selecting = 1;
							}
						}
					}
				}
			}
		}
	}
}

void ScenePlay::cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
	int mouse = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	switch (mouse) {
	case GLFW_PRESS: {
		if (dragging) {
			MathHelper::Line ray = mainCamera->screenToWorldLine((float)xpos, (float)ypos);
			MathHelper::Plane plane = MathHelper::Plane(0.0f, 1.0f, 0.0f, 0.0f);
			vec3 point = MathHelper::pointLinePlane(ray, plane);
			dragShip->setPosition(point);
		}
		break;
	}
	case GLFW_RELEASE: {
		if (dragging) {
			MathHelper::Line ray = mainCamera->screenToWorldLine((float)xpos, (float)ypos);
			MathHelper::Plane plane = MathHelper::Plane(0.0f, 1.0f, 0.0f, 0.0f);
			vec3 point = MathHelper::pointLinePlane(ray, plane);
			for (GameObject* obj : childList) {
				Platform* platform = dynamic_cast<Platform*>(obj);
				if (platform != nullptr) {
					if (platform->inBound(point)) {
						vec2 location = platform->getLocation();
						GameMap::TYPE type = getGameMap()->getPlatformType(location);
						if (type == GameMap::NORMAL || (type == GameMap::SHORT && !dragShip->isLongDistance())
							|| (type == GameMap::LONG && dragShip->isLongDistance())) {
							if (!isPlaced(location)) {
								dragShip->setStatus(Character::STAND);
								dragShip->setPosition(obj->getPosition());
								dragShip->setLayer(CHARACTER);
								addCharacter(location, dragShip);
								ButtonSelecting* btnSelecting = new ButtonSelecting();
								dragShip->addChild(btnSelecting);
								btnSelecting->setLayer(-1);
								btnSelecting->setPosition(vec3(-1.5f, 0.0f, -1.5f));
								btnSelecting->enableAbsoluteScale();
								btnSelecting->enableAbsoluteRotation();
								btnSelecting->setRotation(-90.0f, 0.0f, 0.0f);

								dragging = false;
								dragShip = nullptr;

								selecting = 1;
							}
						}
						break;
					}
				}
			}
			if (dragging) {
				increaseEnergy(dragShip->getEnergy());
				removeObject(dragShip);
				dragging = false;
				dragShip = nullptr;
				dragBtn->clearCooldown();
				dragBtn = nullptr;
			}
		}
		break;
	}
	}
}

void ScenePlay::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS || action == GLFW_REPEAT) {
		vec3 cameraPos = mainCamera->getPosition();
		float d = 1.0f;
		GameMap* gameMap = getGameMap();
		float row = (float)gameMap->getRow();
		float col = (float)gameMap->getColumn();
		switch (key) {
		case GLFW_KEY_W: {
			if (cameraPos.z - d >= -row / 2.0f) {
				moveCamera(vec3(0.0f, 0.0f, -d));
			}
			break;
		}
		case GLFW_KEY_A: {
			if (cameraPos.x - d >= -col / 2.0f) {
				moveCamera(vec3(-d, 0.0f, 0.0f));
			}
			break;
		}
		case GLFW_KEY_S: {
			if (cameraPos.z + d <= row / 2.0f) {
				moveCamera(vec3(0.0f, 0.0f, d));
			}
			break;
		}
		case GLFW_KEY_D: {
			if (cameraPos.x + d <= col / 2.0f) {
				moveCamera(vec3(d, 0.0f, 0.0f));
			}
			break;
		}
		}
	}
}

bool ScenePlay::isPlaced(vec2 location) {
	return isPlaced(round(location.x), round(location.y));
}

bool ScenePlay::isPlaced(int x, int y) {
	return slotList[x][y].ship != nullptr;
}

void ScenePlay::updateBtnSelectCardList() {
	for (int i = 0; i < btnSelectCardList.size(); ++i) {
		btnSelectCardList[i]->setPosition(-8.0f, 4.5f - (float)i * 1.5f);
	}
}

void ScenePlay::moveCamera(vec3 distance) {
	mainCamera->setPosition(mainCamera->getPosition() + distance);
	barHp->setPosition(barHp->getPosition() + distance);
}

int ScenePlay::getBarHpBossCount() {
	getWidgetList();
	int cnt = 0;
	for (Widget* widget : widgetList) {
		if (widget->getName() == "BarHpBoss") {
			cnt++;
		}
	}
	return cnt;
}

void ScenePlay::moveBarHpBoss() {
	getWidgetList();
	for (Widget* widget : widgetList) {
		if (widget->getName() == "BarHpBoss") {
			widget->setPosition(widget->getPosition() + vec3(0.0f, 1.0f, 0.0f));
		}
	}
}

void ScenePlay::addCharacter(vec2 location, Character* charac) {
	addCharacter(round(location.x), round(location.y), charac);
}

void ScenePlay::addCharacter(int x, int y, Character* charac) {
	charac->setLocation(x, y);
	charac->setPosition(locationPosition[vec2(x, y)]);
	if (dynamic_cast<AirCraft*>(charac)) {
		slotList[x][y].airCraftList.emplace_back(dynamic_cast<AirCraft*>(charac));
		charac->setPosition(charac->getPosition() + vec3(0.0f, 1.0f, 0.0f));
	} else {
		if (charac->isEnemy()) {
			Siren* siren = dynamic_cast<Siren*>(charac);
			slotList[x][y].sirenList.emplace_back(siren);
			if (siren->isBoss()) {
				int cnt = getBarHpBossCount();
				BarHpBoss* barHp = new BarHpBoss(!(cnt & 1));
				barHp->setLayer(0);
				barHp->enableAbsolutePosition();
				barHp->enableAbsoluteRotation();
				barHp->enableAbsoluteScale();
				barHp->setPosition(-5.0f, 4.5f - cnt);
				barHp->setRotation(mainCamera->getPitch(), 0.0f, 0.0f);
				siren->addChild(barHp);
				return;
			}
		} else {
			slotList[x][y].ship = dynamic_cast<Ship*>(charac);
		}
	}
	BarHp* barHp = new BarHp();
	barHp->setPosition(vec3(-0.5f, 0.0f, 0.1f));
	barHp->enableAbsoluteScale();
	barHp->enableAbsoluteRotation();
	barHp->setRotation(mainCamera->getPitch(), 0.0f, 0.0f);
	barHp->setLayer(0);
	charac->addChild(barHp);
}

void ScenePlay::removeCharacter(vec2 location, Character* charac) {
	removeCharacter(round(location.x), round(location.y), charac);
}

void ScenePlay::removeCharacter(int x, int y, Character* charac) {
	if (dynamic_cast<AirCraft*>(charac)) {
		AirCraft* aircraft = (AirCraft*)charac;
		for (auto iter = slotList[x][y].airCraftList.begin(); iter != slotList[x][y].airCraftList.end(); ++iter) {
			if (*iter == aircraft) {
				slotList[x][y].airCraftList.erase(iter);
				break;
			}
		}
	} else {
		if (charac->isEnemy()) {
			Siren* siren = dynamic_cast<Siren*>(charac);
			for (auto iter = slotList[x][y].sirenList.begin(); iter != slotList[x][y].sirenList.end(); ++iter) {
				if (*iter == siren) {
					slotList[x][y].sirenList.erase(iter);
					break;
				}
			}
			if (siren->isBoss()) {
				moveBarHpBoss();
			}
		} else {
			slotList[x][y].ship = nullptr;
			slotList[x][y].blockList.clear();
		}
	}
	removeObject(charac);
}

vector<Siren*> ScenePlay::getSirenList(vec2 location) {
	return getSirenList(round(location.x), round(location.y));
}

vector<Siren*> ScenePlay::getSirenList(int x, int y) {
	if (0 <= x && x < getGameMap()->getRow() && 0 <= y && y < getGameMap()->getColumn()) {
		return slotList[x][y].sirenList;
	} else {
		return vector<Siren*>();
	}
}

vector<AirCraft*> ScenePlay::getAirCraftList(vec2 location) {
	return getAirCraftList(round(location.x), round(location.y));
}

vector<AirCraft*> ScenePlay::getAirCraftList(int x, int y) {
	if (0 <= x && x < getGameMap()->getRow() && 0 <= y && y < getGameMap()->getColumn()) {
		return slotList[x][y].airCraftList;
	} else {
		return vector<AirCraft*>();
	}
}

GameMap* ScenePlay::getGameMap() {
	return Game::getInstance()->getResourceManager()->getMapManager()->getGameMap(mapID);
}

vec3 ScenePlay::getPositionByLocation(vec2 location) {
	auto iter = locationPosition.find(location);
	if (iter != locationPosition.end()) {
		return iter->second;
	}
	return vec3(-1.0f, -1.0f, -1.0f);
}

vec3 ScenePlay::getPositionByLocation(int x, int y) {
	return getPositionByLocation(vec2(x, y));
}

void ScenePlay::changeLocation(Character* charac, int oldX, int oldY, int newX, int newY) {
	if (dynamic_cast<AirCraft*>(charac) != nullptr) {
		AirCraft* aircraft = (AirCraft*)charac;
		for (auto iter = slotList[oldX][oldY].airCraftList.begin(); iter != slotList[oldX][oldY].airCraftList.end(); ++iter) {
			if (*iter == aircraft) {
				slotList[oldX][oldY].airCraftList.erase(iter);
				break;
			}
		}
		slotList[newX][newY].airCraftList.emplace_back(aircraft);
	} else if (charac->isEnemy()) {
		Siren* siren = dynamic_cast<Siren*>(charac);
		for (auto iter = slotList[oldX][oldY].sirenList.begin(); iter != slotList[oldX][oldY].sirenList.end(); ++iter) {
			if (*iter == siren) {
				slotList[oldX][oldY].sirenList.erase(iter);
				break;
			}
		}
		slotList[newX][newY].sirenList.emplace_back(siren);
	} else {
		throw DebugHelper::UndefineOperationException();
	}
}

void ScenePlay::changeLocation(Character* charac, vec2 oldLocation, vec2 newLocation) {
	changeLocation(charac, round(oldLocation.x), round(oldLocation.y), round(newLocation.x), round(newLocation.y));
}

int ScenePlay::getEnergy() {
	return energy;
}

void ScenePlay::increaseEnergy(int inc) {
	energy += inc;
}

void ScenePlay::decreaseEnergy(int dec) {
	energy -= dec;
}

void ScenePlay::increaseEnemyDown() {
	enemyDown++;
}

bool ScenePlay::isRunning() {
	return running;
}

void ScenePlay::run() {
	removeObject(btnFormation);
	removeObject(btnCombat);
	btnFormation = nullptr;
	btnCombat = nullptr;
	textEnergy = new Text();
	textEnergy->setLayer(UI);
	textEnergy->setPosition(-6.2f, -4.2f);
	textEnergy->setScale(0.0075f);
	addObject(textEnergy);
	energy = getGameMap()->getEnergy();
	enemyDown = 0;
	running = true;
}

void ScenePlay::stop() {
	prevRunning = running;
	running = false;
}

void ScenePlay::unstop() {
	running = prevRunning;
}

void ScenePlay::succeed() {
	running = false;
	Picture* picture = new Picture("Win", vec2(16.0f, 9.0f), vec2(0.0f, 0.0f), vec2(1280.0f, 720.0f));
	picture->setLayer(UIRESULT);
	picture->setPosition(-8.0f, 4.5f);
	addObject(picture);
}

void ScenePlay::fail() {
	running = false;
	Picture* picture = new Picture("Lose", vec2(16.0f, 9.0f), vec2(0.0f, 0.0f), vec2(1280.0f, 720.0f));
	picture->setLayer(UIRESULT);
	picture->setPosition(-8.0f, 4.5f);
	addObject(picture);
}

vector<GameObject*> ScenePlay::getCollision(GameObject* object, float radius) {
	vector<GameObject*> result;
	for (GameObject* obj : childList) {
		if (obj != nullptr) {
			if (dynamic_cast<Widget*>(obj) == nullptr) {
				if (length(obj->getPosition() - object->getPosition()) < radius) {
					result.emplace_back(obj);
				}
			}
		}
	}
	return result;
}

bool ScenePlay::blockCharacter(vec2 location, Character* charac) {
	return blockCharacter(round(location.x), round(location.y), charac);
}

bool ScenePlay::blockCharacter(int x, int y, Character* charac) {
	if (0 <= x && x < getGameMap()->getRow() && 0 <= y && y < getGameMap()->getColumn()) {
		if (charac->isEnemy()) {
			if (slotList[x][y].ship == nullptr) return false;
			Siren* siren = dynamic_cast<Siren*>(charac);
			if (slotList[x][y].blockList.find(siren) != slotList[x][y].blockList.end()) return true;
			if (slotList[x][y].blockList.size() < slotList[x][y].ship->getMaxBlock()) {
				slotList[x][y].blockList.insert(siren);
				return true;
			} else {
				return false;
			}
		} else {
			throw DebugHelper::UndefineOperationException();
		}
	}
	return false;
}

bool ScenePlay::unblockCharacter(vec2 location, Character* charac) {
	return unblockCharacter(round(location.x), round(location.y), charac);
}

bool ScenePlay::unblockCharacter(int x, int y, Character* charac) {
	if (0 <= x && x < getGameMap()->getRow() && 0 <= y && y < getGameMap()->getColumn()) {
		if (charac->isEnemy()) {
			if (slotList[x][y].ship == nullptr) return false;
			return slotList[x][y].blockList.erase(dynamic_cast<Siren*>(charac));
		} else {
			throw DebugHelper::UndefineOperationException();
		}
	}
	return false;
}

int ScenePlay::getHp() {
	return hp;
}

int ScenePlay::getMaxHp() {
	return maxHp;
}

void ScenePlay::getDamge(int damage) {
	hp -= damage;
	if (hp <= 0) {
		hp = 0;
		fail();
	}
}

bool ScenePlay::addBtnSelectCard(string ship) {
	if (btnSelectCardList.size() == 6) {
		return false;
	}
	ButtonSelectCard* btn = new ButtonSelectCard(dynamic_cast<Ship*>(Game::getInstance()->getRegistration()->getGameObject(ship)));
	btn->setLayer(UI);
	btnSelectCardList.emplace_back(btn);
	addObject(btn);
	updateBtnSelectCardList();
	return true;
}

bool ScenePlay::removeBtnSelectCard(string ship) {
	for (auto iter = btnSelectCardList.begin(); iter != btnSelectCardList.end(); ++iter) {
		if ((*iter)->getShipName() == ship) {
			removeChild(*iter);
			btnSelectCardList.erase(iter);
			updateBtnSelectCardList();
			return true;
		}
	}
	return true;
}

bool ScenePlay::isLegalLocation(vec2 location) {
	return isLegalLocation(round(location.x), round(location.y));
}

bool ScenePlay::isLegalLocation(int x, int y) {
	int row = getGameMap()->getRow(), col = getGameMap()->getColumn();
	return 0 <= x && x < row && 0 <= y && y < col;
}

Ship* ScenePlay::getShip(vec2 location) {
	return getShip(round(location.x), round(location.y));
}

Ship* ScenePlay::getShip(int x, int y) {
	if (0 <= x && x < getGameMap()->getRow() && 0 <= y && y < getGameMap()->getColumn()) {
		return slotList[x][y].ship;
	} else {
		return nullptr;
	}
}
