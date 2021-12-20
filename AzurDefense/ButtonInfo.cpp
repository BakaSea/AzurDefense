#include "ButtonInfo.h"
#include "Game.h"

ButtonInfo::ButtonInfo(string infoName, ButtonCancel* btnCancel, ButtonConfirm* btnConfirm) {
	name = "ButtonInfo";
	size = vec2(16.0f, 9.0f);
	setPosition(-8.0f, 4.5f);
	clickable = true;
	this->infoName = infoName;
	addChild(btnCancel);
	addChild(btnConfirm);
	btnCancel->setLayer(1);
	btnConfirm->setLayer(1);
	btnCancel->enableAbsolutePosition();
	btnConfirm->enableAbsolutePosition();
	btnCancel->setPosition(-3.0f + 1.0f, 2.0f - 3.3f);
	btnConfirm->setPosition(-3.0f + 5.0f - 1.4f, 2.0f - 3.3f);
}

void ButtonInfo::render() {
	renderLowerChild();
	Texture2D* bg = Game::getInstance()->getResourceManager()->getTexture("UI/BlackAlpha");
	Game::getInstance()->getRenderer2D()->renderUI(bg, getPosition(), getRotateZ(), getSize(), getScaling(), vec2(0.0f, 0.0f), vec2(512.0f, 512.0f));
	Texture2D* info = Game::getInstance()->getResourceManager()->getTexture("UI/Info/" + infoName);
	Game::getInstance()->getRenderer2D()->renderUI(info, vec2(-3.0f, 2.0f), getRotateZ(), vec2(6.0f, 4.0f), getScaling(), vec2(0.0f, 0.0f), vec2(600.0f, 400.0f));
	renderUpperChild();
}
