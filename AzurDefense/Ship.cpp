#include "Ship.h"
#include "ScenePlay.h"
#include "Game.h"
#include "Siren.h"

Ship::Ship() {
	cooldown = 0.0f;
	playSetSound = false;
}

void Ship::start() {
	Character::start();
	playSetSound = false;
}

void Ship::update() {
	ScenePlay* scene = dynamic_cast<ScenePlay*>(Game::getInstance()->getSceneController()->getCurrentScene());
	if (scene != nullptr) {
		if (scene->isRunning()) {
			GameObject::update();
			if (status != DRAG) {
				if (hasSound()) {
					if (!playSetSound) {
						Game::getInstance()->getSoundEngine()->play2D(Game::getInstance()->getResourceManager()->getSound(getName() + "/Set"));
						playSetSound = true;
					}
				}
				if (status == DEAD) {
					if (isDead()) {
						scene->removeCharacter(getLocation(), this);
					}
					return;
				}
				if (hp <= 0) {
					if (hasSound()) {
						Game::getInstance()->getSoundEngine()->play2D(Game::getInstance()->getResourceManager()->getSound(getName() + "/Dead"));
					}
					setStatus(DEAD);
					return;
				}
				if (airDefCD->timeOut() && hasAirCraftInRange()) {
					attackAirCraft();
				}
				if (status == SKILL) {
					if (!currentAnimation->isPlaying()) {
						setStatus(STAND);
					}
				} else {
					if (attackCD->timeOut() && hasEnemyInRange()) {
						if (status != ATTACK) {
							setStatus(ATTACK);
						}
						attackEnemy();
					} else {
						if (status != STAND) {
							setStatus(STAND);
						}
					}
				}
				
			}
		}
	}
}

string Ship::getRarity() {
	return "R";
}

float Ship::getCooldown() {
	return cooldown;
}

bool Ship::isLongDistance() {
	return false;
}

bool Ship::canSelected() {
	return true;
}

bool Ship::hasEnemyInRange() {
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
				if (siren->isEnemy() ^ isEnemy()) {
					if (siren->getStatus() != DEAD) {
						enemyList.emplace_back(siren);
					}
				}
			}
		}
	}
	return !enemyList.empty();
}

bool Ship::hasSound() {
	return true;
}
