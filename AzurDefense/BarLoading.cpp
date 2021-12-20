#include "BarLoading.h"
#include "Game.h"

BarLoading::BarLoading() {
	name = "BarLoading";
	size = vec2(16.0f, 0.3125f);
}

void BarLoading::render() {
	Texture2D* texture = Game::getInstance()->getResourceManager()->getTexture("UI/BarLoading");
	Game::getInstance()->getRenderer2D()->renderUI(texture, getPosition(), getRotateZ(), getSize(), getScaling(), vec2(0.0f, 25.0f), vec2(1280.0f, 25.0f));
	vec2 barSize = getSize();
	float rate = (float)Game::getInstance()->getRegistration()->getCurrentRegistry() / (float)Game::getInstance()->getRegistration()->getRegistrySize();
	int barWidth = int(rate * 1280.0f);
	barSize.x *= rate;
	Game::getInstance()->getRenderer2D()->renderUI(texture, getPosition(), getRotateZ(), barSize, getScaling(), vec2(0.0f, 0.0f), vec2(barWidth, 25.0f));
}
