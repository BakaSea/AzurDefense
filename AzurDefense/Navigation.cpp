#include "Navigation.h"
#include "Game.h"
#include "ScenePlay.h"
#include "GameMap.h"

Navigation::Navigation() {
	name = "Navigation";
	size = vec2(0.5f, 0.5f);
	routeID = 0;
	routeIndex = 0;
	velocity = 2.0f;
}

void Navigation::start() {
	routeIndex = 0;
}

void Navigation::update() {
	ScenePlay* scene = dynamic_cast<ScenePlay*>(Game::getInstance()->getSceneController()->getCurrentScene());
	if (scene != nullptr) {
		GameMap* gameMap = scene->getGameMap();
		vec2 nextLocation = gameMap->getRouteLocation(routeID, routeIndex);
		vec3 nextPosition = scene->getPositionByLocation(nextLocation);
		if (getPosition() == nextPosition) {
			routeIndex++;
			if (routeIndex == gameMap->getRouteSize(routeID)) {
				remove();
				return;
			}
		} else {
			vec3 direction = nextPosition - getPosition();
			vec3 distance = normalize(direction) * velocity * (float)Game::getInstance()->getDeltaTime() / 1000.0f;
			if (length(direction) < length(distance)) {
				distance = direction;
			}
			setPosition(getPosition() + distance);
			if (direction.x > 0.0f) {
				setRotation(rotateX, rotateY, 0.0f);
			} else if (direction.x < 0.0f) {
				setRotation(rotateX, rotateY, 180.0f);
			} else if (direction.z < 0.0f) {
				setRotation(rotateX, rotateY, 90.0f);
			} else if (direction.z > 0.0f) {
				setRotation(rotateX, rotateY, -90.0f);
			}
		}
	}
}

GameObject* Navigation::createInstance() {
	return new Navigation();
}

void Navigation::setRoute(int id) {
	routeID = id;
}
