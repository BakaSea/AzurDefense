#include "BarHp.h"
#include "Game.h"
#include "Character.h"
#include "ScenePlay.h"

BarHp::BarHp() {
	name = "BarHp";
	size = vec2(1.0f, 0.1f);
}

void BarHp::render() {
	renderLowerChild();
	Texture2D* texture = Game::getInstance()->getResourceManager()->getTexture("UI/BarHp");
	Game::getInstance()->getRenderer2D()->renderUI3D(texture, getPosition(), size, getRotateX(), getRotateY(), getRotateZ(), getScaling(), vec2(0.0f, 0.0f), vec2(200.0f, 20.0f));
	vec2 barSize = size;
	int barWidth = 0;
	if (dynamic_cast<Character*>(parentObject) != nullptr) {
		Character* charac = dynamic_cast<Character*>(parentObject);
		if (charac->isEnemy()) {
			texture = Game::getInstance()->getResourceManager()->getTexture("UI/BarHpEnemy");
		}
		barWidth = (int)((float)charac->getHp() / (float)charac->getMaxHp() * 200.0f);
		barSize.x = (float)charac->getHp() / (float)charac->getMaxHp() * barSize.x;
	} else if (dynamic_cast<ScenePlay*>(parentObject) != nullptr) {
		ScenePlay* scene = dynamic_cast<ScenePlay*>(parentObject);
		barWidth = (int)((float)scene->getHp() / (float)scene->getMaxHp() * 200.0f);
		barSize.x = (float)scene->getHp() / (float)scene->getMaxHp() * barSize.x;
	}
	Game::getInstance()->getRenderer2D()->renderUI3D(texture, getPosition(), barSize, getRotateX(), getRotateY(), getRotateZ(), getScaling(), vec2(0.0f, 20.0f), vec2((float)barWidth, 20.0f));
	renderUpperChild();
}

bool BarHp::is3D() {
	return true;
}
