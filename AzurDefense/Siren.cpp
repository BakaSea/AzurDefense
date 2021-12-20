#include "Siren.h"
#include "ScenePlay.h"
#include "Game.h"
#include "DebugHelper.h"
#include "Ship.h"

Siren::Siren() {
	routeID = 0;
	routeIndex = 0;
	status = MOVE;
	velocity = 0.0f;
}

void Siren::update() {
	ScenePlay* scene = dynamic_cast<ScenePlay*>(Game::getInstance()->getSceneController()->getCurrentScene());
	if (scene != nullptr) {
		if (scene->isRunning()) {
			GameObject::update();
			if (status == DEAD) {
				if (isDead()) {
					scene->increaseEnergy(getEnergy());
					scene->increaseEnemyDown();
					scene->unblockCharacter(scene->getGameMap()->getRouteLocation(routeID, routeIndex), this);
					scene->removeCharacter(getLocation(), this);
				}
				return;
			}
			if (hp <= 0) {
				setStatus(DEAD);
				return;
			}
			if (airDefCD->timeOut() && hasAirCraftInRange()) {
				attackAirCraft();
			}
			if (skillCD != nullptr) {
				if (skillCD->timeOut()) {
					useSkill();
				}
			}
			if (attackCD->timeOut() && hasEnemyInRange()) {
				if (status != ATTACK) {
					setStatus(ATTACK);
				}
				attackEnemy();
			} else {
				if (status != MOVE) {
					setStatus(MOVE);
				}
				GameMap* gameMap = scene->getGameMap();
				vec2 nextLocation = gameMap->getRouteLocation(routeID, routeIndex);
				vec3 nextPosition = scene->getPositionByLocation(nextLocation);
				if (getPosition() == nextPosition) {
					routeIndex++;
					scene->unblockCharacter(nextLocation, this);
					scene->changeLocation(this, location, nextLocation);
					setLocation(nextLocation);
					if (routeIndex == gameMap->getRouteSize(routeID)) {
						scene->getDamge(energy);
						scene->increaseEnemyDown();
						scene->removeCharacter(nextLocation, this);
						return;
					}
					nextLocation = gameMap->getRouteLocation(routeID, routeIndex);
					nextPosition = scene->getPositionByLocation(nextLocation);
					vec3 direction = nextPosition - getPosition();
					if (direction.x > 0.0f) {
						setOrient(RIGHT);
					} else if (direction.x < 0.0f) {
						setOrient(LEFT);
					} else if (direction.z < 0.0f) {
						setOrient(UP);
					} else if (direction.z > 0.0f) {
						setOrient(DOWN);
					}
				} else {
					if (!scene->blockCharacter(nextLocation, this)) {
						vec3 direction = nextPosition - getPosition();
						vec3 distance = normalize(direction) * velocity * (float)Game::getInstance()->getDeltaTime() / 1000.0f;
						if (length(direction) < length(distance)) {
							distance = direction;
						}
						setPosition(getPosition() + distance);
						if (direction.x > 0.0f) {
							setOrient(RIGHT);
						} else if (direction.x < 0.0f) {
							setOrient(LEFT);
						} else if (direction.z < 0.0f) {
							setOrient(UP);
						} else if (direction.z > 0.0f) {
							setOrient(DOWN);
						}
					}
				}
			}
		}
	}
}

bool Siren::isEnemy() {
	return true;
}

void Siren::setRoute(int id) {
	routeID = id;
}

bool Siren::isBoss() {
	return false;
}

void Siren::useSkill() {
	if (skillCD->timeOut()) {
		doSkill();
		skillCD->start();
	}
}

bool Siren::hasEnemyInRange() {
	enemyList.clear();
	ScenePlay* scene = dynamic_cast<ScenePlay*>(Game::getInstance()->getSceneController()->getCurrentScene());
	if (scene != nullptr) {
		for (vec2& range : attackRange) {
			mat4 model = MathHelper::getModelMatrix(vec3(0.0f), 0.0f, 0.0f, orientDegree, vec2(1.0f, 1.0f), vec2(1.0f, 1.0f));
			vec4 point(range, 0.0f, 0.0f);
			point = model * point;
			vec2 loc(point);
			Ship* ship = scene->getShip(getLocation() + loc);
			if (ship != nullptr) {
				if (ship->getStatus() != DEAD) {
					enemyList.emplace_back(ship);
				}
			}
		}
	}
	return !enemyList.empty();
}
