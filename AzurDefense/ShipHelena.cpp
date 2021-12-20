#include "ShipHelena.h"
#include "MissleHE.h"
#include "BuffDamagedImpRate.h"

ShipHelena::ShipHelena() {
	name = "Helena";
	size = vec2(2.0f, 2.0f);
	animateList.emplace_back(new Animation("Drag", 11, vec2(0.0f, -0.2f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Stand", 13, vec2(0.0f, -0.1f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Attack", 8, vec2(0.0f, -0.1f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Dead", 8, vec2(0.4f, -0.4f), vec2(1.0f / 0.8f, 1.0f / 0.8f)));
	animateList.emplace_back(new Animation("Skill", 8, vec2(0.0f, -0.15f), vec2(1.0f, 1.0f), true));
	currentAnimation = animateList[0];
	armor = LIGHT;
	maxHp = 1500;
	atk = 280;
	airDef = 300;
	energy = 5;
	maxBlock = 0;
	cooldown = 5.0f;
	attackFrame = 3;
	deadFrame = 7;
	attackRange = {
		vec2(0.0f, 1.0f), vec2(0.0f, 2.0f), vec2(0.0f, 3.0f), vec2(0.0f, 4.0f), vec2(0.0f, 5.0f)
	};
	airDefRange = {
		vec2(-1.0f, -1.0f), vec2(-1.0f, 0.0f), vec2(-1.0f, 1.0f),
		vec2(0.0f, -1.0f), vec2(0.0f, 0.0f), vec2(0.0f, 1.0f),
		vec2(1.0f, -1.0f), vec2(1.0f, 0.0f), vec2(1.0f, 1.0f)
	};
	addChild(attackCD = new Timer(Timer::COUNTDOWN, 1500, false, Timer::FUNCNULL));
	addChild(airDefCD = new Timer(Timer::COUNTDOWN, 200, false, Timer::FUNCNULL));
	addChild(skillCD = new Timer(Timer::COUNTDOWN, 20000, false, Timer::FUNCNULL));
}

GameObject* ShipHelena::createInstance() {
	return new ShipHelena();
}

string ShipHelena::getRarity() {
	return "SR";
}

bool ShipHelena::isLongDistance() {
	return true;
}

void ShipHelena::doAttack() {
	createThrowingObject(new MissleHE(), 10.0f, 3.0f, calculateDamage(nullptr) / 3.0f, 3.0f, vec2(0.5f, 0.3f), vec2(1.2f, 1.2f));
}

void ShipHelena::doSkill() {
	if (hasEnemyInRange()) {
		for (Character* enemy : enemyList) {
			enemy->addChild(new BuffDamagedImpRate(0.3f, 10000));
		}
	}
}
