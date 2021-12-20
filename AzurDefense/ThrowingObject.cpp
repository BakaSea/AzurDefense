#include "ThrowingObject.h"
#include "Game.h"
#include "ScenePlay.h"
#include "DebugHelper.h"
#include "Platform.h"

ThrowingObject::ThrowingObject() {
	velocity = vec3(0.0f, 0.0f, 0.0f);
	damage = 0.0f;
	fromEnemy = false;
	hasGravity = true;
	g = vec3(0.0f, -1.0f, 0.0f);
	radius = 0.5f;
	totalTime = 0;
}

void ThrowingObject::start() {
	this->totalTime = 0;
}

void ThrowingObject::update() {
	ScenePlay* scene = dynamic_cast<ScenePlay*>(Game::getInstance()->getSceneController()->getCurrentScene());
	if (scene != nullptr) {
		if (scene->isRunning()) {
			totalTime += Game::getInstance()->getDeltaTime();
			if (totalTime > 10000) {
				remove();
				return;
			}
			position += velocity * (float)Game::getInstance()->getDeltaTime() / 1000.0f;
			if (hasGravity) {
				velocity += g * (float)Game::getInstance()->getDeltaTime() / 1000.0f;
			}
			changeRotation();
			bool flag = false;
			vector<GameObject*> collision = scene->getCollision(this, radius);
			for (GameObject* obj : collision) {
				Character* charac = dynamic_cast<Character*>(obj);
				if (charac != nullptr) {
					if (charac->isEnemy() ^ fromEnemy) {
						flag = true;
						doAttack(charac);
					}
				}
				if (hasGravity) {
					if (getPosition().y <= 0.0f) {
						flag = true;
						break;
					}
				}
				if (obj->getName() == "PlatformObstacle" && getPosition().y <= 0.31f) {
					flag = true;
					break;
				}
			}
			if (flag) {
				remove();
				return;
			}
		}
	}
}

void ThrowingObject::enableGravity() {
	hasGravity = true;
}

void ThrowingObject::disableGravity() {
	hasGravity = false;
}

void ThrowingObject::setEnemy(bool fromEnemy) {
	this->fromEnemy = fromEnemy;
}

void ThrowingObject::setDamage(float damage) {
	this->damage = damage;
}

void ThrowingObject::aim(vec3 source, vec3 velocity) {
	setPosition(source);
	this->velocity = velocity;
}

void ThrowingObject::aim(vec3 source, vec3 target, float time) {
	setPosition(source);
	vec3 distance = target - source;
	this->velocity = distance / time - 0.5f * g * time;
}

void ThrowingObject::doAttack(GameObject* object) {
	if (dynamic_cast<Character*>(object) != nullptr) {
		Character* charac = (Character*)object;
		charac->getDamaged(calculateDamage(charac));
	}
}

float ThrowingObject::calculateDamage(GameObject* object) {
	return damage;
}

void ThrowingObject::changeRotation() {
	if (hasGravity) {
		if (velocity.x >= 0.0f) {
			setRotation(rotateX, 0.0f, degrees(atan(velocity.y / velocity.x)));
		} else {
			setRotation(rotateX, 0.0f, 180.0f + degrees(atan(velocity.y / velocity.x)));
		}
	} else {
		if (velocity.x >= 0.0f) {
			setRotation(rotateX, 0.0f, -degrees(atan(velocity.z / velocity.x)));
		} else {
			setRotation(rotateX, 0.0f, 180.0f - degrees(atan(velocity.z / velocity.x)));
		}
	}
}
