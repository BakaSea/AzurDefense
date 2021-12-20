#include "Registry.h"
#include <stdlib.h>
#include <string.h>
#include "Game.h"
#include "DebugHelper.h"
#include "Ship.h"
#include "Platform.h"
#include "PlatformObstacle.h"
#include "PlatformStart.h"
#include "PlatformEnd.h"
#include "PlatformShort.h"
#include "PlatformLong.h"
#include "Navigation.h"
#include "ShipAyanami.h"
#include "ShipJavelin.h"
#include "ShipZ23.h"
#include "ShipLaffey.h"
#include "ShipKashino.h"
#include "ShipBullin.h"
#include "ShipBullinMKII.h"
#include "ShipSaratoga.h"
#include "ShipCheshire.h"
#include "ShipNewJersey.h"
#include "ShipNagato.h"
#include "ShipHelena.h"
#include "ShipShimakaze.h"
#include "SirenScavenger.h"
#include "SirenSmasher.h"
#include "SirenConductor.h"
#include "SirenPurifier.h"
#include "SirenLurker.h"
#include "SirenChaser.h"
#include "SirenNavigator.h"
#include "SirenTester.h"
#include "SirenZero.h"
#include "EShipRepair.h"
#include "MissleNormal.h"
#include "MissleHE.h"
#include "MissleAP.h"
#include "Torpedo.h"
#include "Bomb.h"
#include "ACFighter.h"
#include "ACBomber.h"
#include "ACTorpedo.h"
#include "BuffAirDef.h"
#include "BuffHeal.h"
#include "BuffIgnited.h"
#include "BuffLeaked.h"

Registry::Registry() {
	registerTexture("UI/StartMenu");
	registerTexture("UI/Logo");
	registerTexture("UI/BarLoading");
	objects = {
		new Platform(),
		new PlatformObstacle(),
		new PlatformStart(),
		new PlatformEnd(),
		new PlatformShort(),
		new PlatformLong(),
		new Navigation(),
		new ShipAyanami(),
		new ShipJavelin(),
		new ShipZ23(),
		new ShipLaffey(),
		new ShipKashino(),
		new ShipBullin(),
		new ShipBullinMKII(),
		new ShipSaratoga(),
		new ShipCheshire(),
		new ShipNewJersey(),
		new ShipNagato(),
		new ShipHelena(),
		new ShipShimakaze(),
		new SirenScavenger(),
		new SirenSmasher(),
		new SirenConductor(),
		new SirenPurifier(),
		new SirenLurker(),
		new SirenChaser(),
		new SirenNavigator(),
		new SirenTester(),
		new SirenZero(),
		new EShipRepair(),
		new MissleNormal(),
		new MissleHE(),
		new MissleAP(),
		new Torpedo(),
		new Bomb(),
		new ACFighter(),
		new ACBomber(),
		new ACTorpedo(),
		new BuffAirDef(),
		new BuffHeal(),
		new BuffIgnited(),
		new BuffLeaked()
	};
	widgets = {
		"UI/Background",
		"UI/BGPlayUI",
		"UI/SRBG",
		"UI/SRFrame",
		"UI/SSRBG",
		"UI/SSRFrame",
		"UI/URBG",
		"UI/URFrame",
		"UI/Selecting",
		"UI/BarHp",
		"UI/BarHpEnemy",
		"UI/BlackAlpha",
		"UI/Cooldown",
		"UI/Win",
		"UI/Lose",
		"UI/ButtonAlpha",
		"UI/ButtonStart",
		"UI/ButtonExit",
		"UI/ButtonFormation",
		"UI/ButtonCombat",
		"UI/Info/InfoPlayStop",
		"UI/Info/Cancel",
		"UI/Info/Confirm",
		"UI/ButtonPlayStop",
		"UI/AttackRange",
		"UI/AirRange",
		"UI/SeaEasy",
		"UI/SeaNormal",
		"UI/SeaHard",
		"UI/ButtonFormation",
		"UI/Reward",
		"UI/ButtonBack",
		"UI/MapTitleClear",
		"UI/MapTitleUnclear",
		"UI/BGMap",
		"UI/ButtonContinue",
		"UI/ButtonPrevChapter",
		"UI/ButtonNextChapter",
		"UI/BarHpBoss"
	};
	sounds = {
		"BGMStart",
		"BGMMap",
		"BGMPlay"
	};
	currentRegistry = 0;
}

Registry::Registry(const Registry& A) {
	currentRegistry = A.currentRegistry;
	for (auto i : A.objects) {
		objects.emplace_back(new GameObject(*i));
	}
	for (auto i : A.widgets) {
		widgets.emplace_back(i);
	}
	for (auto i : A.sounds) {
		sounds.emplace_back(i);
	}
}

Registry::~Registry() {
	objects.clear();
	widgets.clear();
	sounds.clear();
	for (auto i : objectList) {
		GameObject*& obj = i.second;
		delete obj;
		obj = nullptr;
	}
	objectList.clear();
}

GameObject* Registry::getGameObject(string name) {
	auto iter = objectList.find(name);
	if (iter == objectList.end()) {
		DebugHelper::logError("Cannot get game object " + name);
		return nullptr;
	}
	GameObject* result = iter->second->createInstance();
	return result;
}

void Registry::init() {
	if (currentRegistry < objects.size()) {
		registerGameObject(objects[currentRegistry]);
		currentRegistry++;
	} else if (currentRegistry - objects.size() < widgets.size()) {
		registerTexture(widgets[currentRegistry - objects.size()]);
		currentRegistry++;
	} else if (currentRegistry - objects.size() - widgets.size() < 1) {
		registerGameMap();
		currentRegistry++;
	} else if (currentRegistry - objects.size() - widgets.size() - 1 < 1) {
		Game::getInstance()->getResourceManager()->readUserData();
		currentRegistry++;
	} else if (currentRegistry - objects.size() - widgets.size() - 2 < sounds.size()) {
		registerSound(sounds[currentRegistry - objects.size() - widgets.size() - 2]);
		currentRegistry++;
	} else {
		throw DebugHelper::UndefineOperationException();
	}
}

int Registry::getRegistrySize() {
	return objects.size() + widgets.size() + 2 + sounds.size();
}

int Registry::getCurrentRegistry() {
	return currentRegistry;
}

void Registry::registerGameObject(GameObject* obj) {
	objectList[obj->getName()] = obj;
	DebugHelper::logInfo("Register " + obj->getName());
	if (obj->hasAnimation()) {
		auto animateInfo = obj->getAnimateInfo();
		for (auto animate : animateInfo) {
			Game::getInstance()->getResourceManager()->registerTexture(obj->getName(), animate.first, animate.second);
		}
	} else {
		Game::getInstance()->getResourceManager()->registerTexture(obj->getName());
	}
	if (dynamic_cast<Ship*>(obj) != nullptr) {
		Game::getInstance()->getResourceManager()->registerTexture(obj->getName() + "/" + obj->getName());
		Game::getInstance()->getResourceManager()->registerTexture(obj->getName() + "/SkillIcon");
		Ship* ship = (Ship*)obj;
		if (ship->hasSound()) {
			Game::getInstance()->getResourceManager()->registerSound(obj->getName() + "/Set");
			Game::getInstance()->getResourceManager()->registerSound(obj->getName() + "/Dead");
			Game::getInstance()->getResourceManager()->registerSound(obj->getName() + "/Skill");
		}
	}
	if (dynamic_cast<Siren*>(obj) != nullptr) {
		if (((Siren*)obj)->isBoss()) {
			Game::getInstance()->getResourceManager()->registerTexture(obj->getName() + "/" + obj->getName());
		}
	}
}

void Registry::registerTexture(string name) {
	Game::getInstance()->getResourceManager()->registerTexture(name);
}

void Registry::registerGameMap() {
	Game::getInstance()->getResourceManager()->registerGameMap();
}

void Registry::registerSound(string name) {
	DebugHelper::logInfo("Register sound for " + name);
	Game::getInstance()->getResourceManager()->registerSound(name);
}
