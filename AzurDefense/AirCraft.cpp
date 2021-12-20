#include "AirCraft.h"
#include "ScenePlay.h"
#include "Game.h"
#include "DebugHelper.h"

AirCraft::AirCraft() {
	energy = 1;
	fromEnemy = false;
	fromCharacter = false;
	velocity = 1.0f;
	front = vec2(0.0f, 0.0f);
	suicide = false;
	bellicose = false;
}

void AirCraft::update() {
	ScenePlay* scene = dynamic_cast<ScenePlay*>(Game::getInstance()->getSceneController()->getCurrentScene());
	if (scene != nullptr) {
		if (scene->isRunning()) {
			GameObject::update();
			if (hp <= 0) {
				if (isEnemy()) {
					if (!fromCharacter) {
						scene->increaseEnemyDown();
					}
					scene->increaseEnergy(getEnergy());
				}
				scene->removeCharacter(getLocation(), this);
				return;
			}
			if (suicide) {
				position += vec3(0, -velocity, 0) * (float)Game::getInstance()->getDeltaTime() / 1000.0f;
				if (getPosition().y <= 0.0f) {
					explode();
				}
				return;
			}
			if (airDefCD->timeOut() && hasAirCraftInRange()) {
				attackAirCraft();
			}
			if (hasEnemyInRange()) {
				if (!hasAttacked) {
					attackEnemy();
					return;
				} else {
					if (bellicose) {
						suicide = true;
						return;
					}
				}
			}
			vec2 nextLocation = getLocation() + front;
			vec3 nextPosition = scene->getPositionByLocation(nextLocation) + vec3(0.0f, 1.0f, 0.0f);
			if (getPosition() == nextPosition) {
				scene->changeLocation(this, getLocation(), nextLocation);
				setLocation(nextLocation);
				nextLocation = getLocation() + front;
				GameMap* gameMap = scene->getGameMap();
				if (gameMap->isEnd(getLocation())) {
					if (isEnemy()) {
						if (!fromCharacter) {
							scene->increaseEnemyDown();
						}
					}
					scene->getDamge(getEnergy());
					scene->removeCharacter(getLocation(), this);
					return;
				}
				if (nextLocation.x < 0 || nextLocation.y < 0 || nextLocation.x >= gameMap->getRow() || nextLocation.y >= gameMap->getColumn()) {
					if (isEnemy()) {
						if (!fromCharacter) {
							scene->increaseEnemyDown();
						}
					}
					scene->removeCharacter(getLocation(), this);
				}
			} else {
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

void AirCraft::setStatus(STATUS status) {
	throw DebugHelper::UndefineOperationException();
}

bool AirCraft::isEnemy() {
	return fromEnemy;
}

void AirCraft::setEnemy(bool fromEnemy) {
	this->fromEnemy = fromEnemy;
}

void AirCraft::setAttack(int atk) {
	this->atk = atk;
}

void AirCraft::setMaxHp(int maxHp) {
	this->maxHp = maxHp;
}

void AirCraft::setAirDef(int airDef) {
	this->airDef = airDef;
}

void AirCraft::setHp(int hp) {
	this->hp = hp;
}

void AirCraft::setFront(vec2 front) {
	this->front = front;
	if (front.x > 0.0f) {
		setOrient(DOWN);
	} else if (front.x < 0.0f) {
		setOrient(UP);
	} else if (front.y > 0.0f) {
		setOrient(RIGHT);
	} else {
		setOrient(LEFT);
	}
}

void AirCraft::setBellicose(bool bellicose) {
	this->bellicose = bellicose;
}

void AirCraft::setCharacter(bool fromCharacter) {
	this->fromCharacter = fromCharacter;
}

bool AirCraft::hasEnemyInRange() {
	enemyList.clear();
	ScenePlay* scene = dynamic_cast<ScenePlay*>(Game::getInstance()->getSceneController()->getCurrentScene());
	if (scene != nullptr) {
		for (vec2& range : attackRange) {
			mat4 model = MathHelper::getModelMatrix(vec3(0.0f), 0.0f, 0.0f, orientDegree, vec2(1.0f, 1.0f), vec2(1.0f, 1.0f));
			vec4 point(range, 0.0f, 0.0f);
			point = model * point;
			vec2 loc(point);
			if (isEnemy()) {
				auto ship = scene->getShip(getLocation() + loc);
				if (ship != nullptr) {
					if (ship->getStatus() != DEAD) {
						enemyList.emplace_back(ship);
					}
				}
			} else {
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
	}
	return !enemyList.empty();
}

void AirCraft::attackAirCraft() {
	for (Character* aircraft : aircraftList) {
		aircraft->getDamaged(calculateDamage(aircraft));
	}
	airDefCD->start();
}

void AirCraft::attackEnemy() {
	doAttack();
	hasAttacked = true;
}

void AirCraft::explode() {
	ScenePlay* scene = dynamic_cast<ScenePlay*>(Game::getInstance()->getSceneController()->getCurrentScene());
	if (scene != nullptr) {
		auto collision = scene->getCollision(this, 0.5f);
		for (auto obj : collision) {
			Character* charac = dynamic_cast<Character*>(obj);
			if (charac != nullptr) {
				if (charac->isEnemy() ^ isEnemy()) {
					charac->getDamaged(calculateDamage(charac));
				}
			}
		}
		if (isEnemy()) {
			if (!fromCharacter) {
				scene->increaseEnemyDown();
			}
		}
		scene->removeCharacter(getLocation(), this);
	}
}
