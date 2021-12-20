#include "SirenConductor.h"
#include "Game.h"
#include "ScenePlay.h"
#include "ACFighter.h"
#include "ACBomber.h"
#include "ACTorpedo.h"

SirenConductor::SirenConductor() {
	name = "Conductor";
	size = vec2(2.0f, 2.0f);
	animateList.emplace_back(new Animation("Move", 48, vec2(0.0f, 0.0f), vec2(1.0f / 0.5f, 1.0f / 0.5f)));
	animateList.emplace_back(new Animation("Attack", 8, vec2(0.0f, 0.0f), vec2(1.0f / 0.5f, 1.0f / 0.5f)));
	animateList.emplace_back(new Animation("Dead", 8, vec2(0.0f, -0.8f), vec2(1.0f / 0.5f, 1.0f / 0.5f)));
	currentAnimation = animateList[0];
	armor = MIDDIUM;
	maxHp = 3000;
	atk = 400;
	attackFrame = 3;
	deadFrame = 7;
	attackRange = {
		vec2(-1.0f, 1.0f), vec2(-1.0f, 2.0f), vec2(-1.0f, 3.0f), vec2(-1.0f, 4.0f),
		vec2(0.0f, 1.0f), vec2(0.0f, 2.0f), vec2(0.0f, 3.0f), vec2(0.0f, 4.0f), vec2(0.0f, 5.0f), vec2(0.0f, 6.0f),
		vec2(1.0f, 1.0f), vec2(1.0f, 2.0f), vec2(1.0f, 3.0f), vec2(1.0f, 4.0f)
	};
	addChild(attackCD = new Timer(Timer::COUNTDOWN, 10000, false, Timer::FUNCNULL));
	addChild(airDefCD = new Timer(Timer::COUNTDOWN, 0, false, Timer::FUNCNULL));
	velocity = 0.15f;
	energy = 5;
}

GameObject* SirenConductor::createInstance() {
	return new SirenConductor();
}

void SirenConductor::doAttack() {
	ScenePlay* scene = dynamic_cast<ScenePlay*>(Game::getInstance()->getSceneController()->getCurrentScene());
	if (scene != nullptr) {
		createAircraft(new ACFighter(), getAttack() / 10, getAirDef(), getMaxHp() / 10, false, vec2(-1.0f, 0.0f), 0);
		createAircraft(new ACBomber(), getAttack(), 0, getMaxHp() / 10, false, vec2(1.0f, 0.0f), 0);
		createAircraft(new ACTorpedo(), getAttack(), 0, getMaxHp() / 10, false, vec2(0.0f, 0.0f), 0);
	}
}
