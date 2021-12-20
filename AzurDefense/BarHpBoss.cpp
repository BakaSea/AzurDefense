#include "BarHpBoss.h"
#include "Game.h"
#include "Character.h"

BarHpBoss::BarHpBoss(bool left) {
	name = "BarHpBoss";
	size = vec2(10.0f, 0.5f);
	this->left = left;
}

void BarHpBoss::render() {
	if (dynamic_cast<Character*>(parentObject) != nullptr) {
		Character* charac = (Character*)parentObject;
		Texture2D* texture = Game::getInstance()->getResourceManager()->getTexture("UI/BarHpBoss");
		Texture2D* boss = Game::getInstance()->getResourceManager()->getTexture(charac->getName() + "/" + charac->getName());
		Renderer2D* renderer = Game::getInstance()->getRenderer2D();
		vec2 barSize = getSize();
		barSize.x *= (float)charac->getHp() / (float)charac->getMaxHp();
		float barWidth = (float)charac->getHp() / (float)charac->getMaxHp() * 400.0f;
		if (left) {
			renderer->renderUI(texture, getPosition(), getRotateZ(), vec2(1.0f, 1.0f), getScaling(), vec2(0.0f, 40.0f), vec2(64.0f, 64.0f));
			renderer->renderUI(boss, getPosition() + vec3(3.0f / 64.0f, -3.0f / 64.0f, 0.0f), getRotateZ(), vec2(58.0f / 64.0f, 58.0f / 64.0f),
				getScaling(), vec2(0.0f, 0.0f), vec2(116.0f, 116.0f));
			renderer->renderUI(texture, getPosition() + vec3(1.0f, -0.25f, 0.0f), getRotateZ(), getSize(), getScaling(), vec2(0.0f, 0.0f), vec2(400.0f, 20.0f));
			renderer->renderUI(texture, getPosition() + vec3(1.0f, -0.25f, 0.0f), getRotateZ(), barSize, getScaling(), vec2(0.0f, 20.0f), vec2(barWidth, 20.0f));
		} else {
			renderer->renderUI(texture, getPosition(), getRotateZ(), getSize(), getScaling(), vec2(0.0f, 0.0f), vec2(400.0f, 20.0f));
			renderer->renderUI(texture, getPosition(), getRotateZ(), barSize, getScaling(), vec2(0.0f, 20.0f), vec2(barWidth, 20.0f));
			renderer->renderUI(texture, getPosition() + vec3(size.x, 0.0f, 0.0f), getRotateZ(), vec2(1.0f, 1.0f), getScaling(), vec2(0.0f, 40.0f), vec2(64.0f, 64.0f));
			renderer->renderUI(boss, getPosition() + vec3(size.x + 3.0f / 64.0f, -3.0f / 64.0f, 0.0f), getRotateZ(), vec2(58.0f / 64.0f, 58.0f / 64.0f),
				getScaling(), vec2(0.0f, 0.0f), vec2(116.0f, 116.0f));
		}
	}
}