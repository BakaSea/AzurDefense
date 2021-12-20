#include "ContainerShip.h"
#include "Game.h"
#include "ButtonSelectCard.h"
#include "Ship.h"
#include <algorithm>

ContainerShip::ContainerShip() : COL(5) {
	name = "ContainerShip";
	size = vec2(7.5f, 7.5f);
}

void ContainerShip::start() {
	vector<string> shipList = Game::getInstance()->getResourceManager()->getUserData()->getShipList();
	vector<Ship*> ships(shipList.size(), nullptr);
	for (int i = 0; i < shipList.size(); ++i) {
		ships[i] = dynamic_cast<Ship*>(Game::getInstance()->getRegistration()->getGameObject(shipList[i]));
	}
	sort(ships.begin(), ships.end(), [](Ship* A, Ship* B) -> bool {
		if (A->getRarity() != B->getRarity()) return MathHelper::getRarityPriority(A->getRarity()) > MathHelper::getRarityPriority(B->getRarity());
		return A->getName() < B->getName();
		});
	for (int i = 0; i < ships.size(); ++i) {
		int x = i % 5, y = i / 5;
		ButtonSelectCard* btn = new ButtonSelectCard(ships[i]);
		btn->setLayer(1);
		vec2 btnSize = btn->getSize();
		btn->setPosition(x * btnSize.x, -y * btnSize.y);
		addChild(btn);
	}
}

void ContainerShip::render() {
	renderLowerChild();
	Texture2D* texture = Game::getInstance()->getResourceManager()->getTexture("UI/BlackAlpha");
	Game::getInstance()->getRenderer2D()->renderUI(texture, getPosition(), getRotateZ(), getSize(), getScaling(), vec2(0.0f, 0.0f), vec2(512.0f, 512.0f));
	renderUpperChild();
}
