#include "EShipRepair.h"
#include "Game.h"
#include "ScenePlay.h"
#include "BuffHeal.h"

EShipRepair::EShipRepair() {
	name = "EShipRepair";
	size = vec2(2.0f, 2.0f);
	animateList.emplace_back(new Animation("Move", 16, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f)));
	animateList.emplace_back(new Animation("Attack", 8, vec2(0.0f, 0.0f), vec2(1.0f, 1.0f)));
	currentAnimation = animateList[0];
	armor = LIGHT;
	maxHp = 500;
	atk = 500;
	attackFrame = 3;
	attackRange.emplace_back(vec2(-1.0f, -1.0f));
	attackRange.emplace_back(vec2(-1.0f, 0.0f));
	attackRange.emplace_back(vec2(-1.0f, 1.0f));
	attackRange.emplace_back(vec2(0.0f, -1.0f));
	attackRange.emplace_back(vec2(0.0f, 0.0f));
	attackRange.emplace_back(vec2(0.0f, 1.0f));
	attackRange.emplace_back(vec2(1.0f, -1.0f));
	attackRange.emplace_back(vec2(1.0f, 0.0f));
	attackRange.emplace_back(vec2(1.0f, 1.0f));
	addChild(attackCD = new Timer(Timer::COUNTDOWN, 5000, false, Timer::FUNCNULL));
	addChild(airDefCD = new Timer(Timer::COUNTDOWN, 0, false, Timer::FUNCNULL));
	velocity = 0.5f;
	energy = 2;
}

GameObject* EShipRepair::createInstance() {
	return new EShipRepair();
}

bool EShipRepair::hasEnemyInRange() {
	enemyList.clear();
	ScenePlay* scene = dynamic_cast<ScenePlay*>(Game::getInstance()->getSceneController()->getCurrentScene());
	if (scene != nullptr) {
		for (vec2& range : attackRange) {
			mat4 model = MathHelper::getModelMatrix(vec3(0.0f), 0.0f, 0.0f, orientDegree, vec2(1.0f, 1.0f), vec2(1.0f, 1.0f));
			vec4 point(range, 0.0f, 0.0f);
			point = model * point;
			vec2 loc(point);
			auto sirenList = scene->getSirenList(getLocation() + loc);
			for (Siren* siren : sirenList) {
				if (siren->getStatus() != DEAD) {
					enemyList.emplace_back(siren);
				}
			}
		}
	}
	return !enemyList.empty();
}

void EShipRepair::doAttack() {
	for (Character* enemy : enemyList) {
		BuffHeal* buf = new BuffHeal(calculateDamage(enemy));
		buf->setLayer(1);
		enemy->addChild(buf);
	}
}
