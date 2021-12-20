#include "BuffBase.h"
#include "Game.h"
#include "ScenePlay.h"

BuffBase::BuffBase() {
	timer = nullptr;
}

BuffBase::BuffBase(int lasting) {
	addChild(timer = new Timer(Timer::COUNTDOWN, lasting, false, Timer::FUNCNULL));
}

BuffBase::~BuffBase() {
	timer = nullptr;
}

void BuffBase::start() {
	GameObject::start();
	startBuff();
}

void BuffBase::update() {
	ScenePlay* scene = dynamic_cast<ScenePlay*>(Game::getInstance()->getSceneController()->getCurrentScene());
	if (scene != nullptr) {
		if (scene->isRunning()) {
			GameObject::update();
			if (timer->timeOut()) {
				endBuff();
				remove();
				return;
			}
			updateBuff();
		}
	}
}

void BuffBase::render() {
	if (getSize() != vec2(0.0f, 0.0f)) {
		GameObject::render();
	}
}

void BuffBase::init() {

}

void BuffBase::startBuff() {

}

void BuffBase::updateBuff() {

}

void BuffBase::endBuff() {

}
