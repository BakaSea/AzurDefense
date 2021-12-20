#include "ShipSaratoga.h"
#include "ACFighter.h"
#include "ACBomber.h"
#include "Game.h"
#include "ScenePlay.h"
#include "MissleHE.h"

ShipSaratoga::ShipSaratoga() {
	name = "Saratoga";
	size = vec2(2.0f, 2.0);
	animateList.emplace_back(new Animation("Drag", 12, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Stand", 16, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Attack", 8, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Dead", 8, vec2(0.3f, -0.5f), vec2(1.0f / 0.9f, 1.0f / 0.9f)));
	animateList.emplace_back(new Animation("Skill", 8, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f), true));
	currentAnimation = animateList[0];
	armor = MIDDIUM;
	maxHp = 3000;
	atk = 1000;
	airDef = 300;
	energy = 10;
	maxBlock = 0;
	cooldown = 10.0f;
	attackFrame = 4;
	deadFrame = 7;
	attackRange = {
		vec2(-1.0f, 1.0f), vec2(-1.0f, 2.0f), vec2(-1.0f, 3.0f), vec2(-1.0f, 4.0f),
		vec2(0.0f, 1.0f), vec2(0.0f, 2.0f), vec2(0.0f, 3.0f), vec2(0.0f, 4.0f), vec2(0.0f, 5.0f), vec2(0.0f, 6.0f),
		vec2(1.0f, 1.0f), vec2(1.0f, 2.0f), vec2(1.0f, 3.0f), vec2(1.0f, 4.0f)
	};
	addChild(attackCD = new Timer(Timer::COUNTDOWN, 10000, false, Timer::FUNCNULL));
	addChild(airDefCD = new Timer(Timer::COUNTDOWN, 0, false, Timer::FUNCNULL));
	addChild(skillCD = new Timer(Timer::COUNTDOWN, 20000, false, Timer::FUNCNULL));
}

GameObject* ShipSaratoga::createInstance() {
	return new ShipSaratoga();
}

string ShipSaratoga::getRarity() {
	return "SR";
}

bool ShipSaratoga::isLongDistance() {
	return true;
}

void ShipSaratoga::doAttack() {
	ScenePlay* scene = dynamic_cast<ScenePlay*>(Game::getInstance()->getSceneController()->getCurrentScene());
	if (scene != nullptr) {
		createAircraft(new ACFighter(), getAttack() / 10, getAirDef(), getMaxHp() / 6, false, vec2(0.0f, 0.0f), 0);
		createAircraft(new ACBomber(), getAttack(), 0, getMaxHp() / 6, false, vec2(1.0f, 0.0f), 0);
		createAircraft(new ACBomber(), getAttack(), 0, getMaxHp() / 6, false, vec2(-1.0f, 0.0f), 0);
	}
}

void ShipSaratoga::doSkill() {
	createThrowingObject(new MissleHE(), 15.0f, 3.0f, calculateDamage(nullptr) / 5.0f, 3, vec2(0.5f, 0.3f), vec2(2.0f, 2.0f));
}
