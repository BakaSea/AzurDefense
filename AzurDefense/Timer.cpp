#include "Timer.h"
#include "Game.h"
#include "DebugHelper.h"

void Timer::FUNCNULL() {
	return;
}

Timer::Timer(TYPE type, int timing, bool timeOutFirst, function<void()> func) {
	this->type = type;
	this->timing = timing;
	this->timeOutFirst = timeOutFirst;
	this->func = func;
	this->timeCount = 0;
	this->firstStart = true;
	this->firstOut = false;
}

void Timer::start() {
	if (firstStart) {
		timeCount = this->timeOutFirst ? timing : 0;
		firstStart = false;
		firstOut = false;
	} else {
		timeCount = 0;
		firstOut = false;
	}
}

void Timer::update() {
	if (timeCount >= timing) {
		if (!firstOut) {
			func();
			firstOut = true;
		}
		if (type == INTERVAL) {
			timeCount = 0;
			firstOut = false;
		}
	} else {
		timeCount += Game::getInstance()->getDeltaTime();
	}
}

void Timer::render() {

}

void Timer::addChild(GameObject* object) {
	throw DebugHelper::UndefineOperationException();
}

void Timer::removeChild(GameObject* object) {
	throw DebugHelper::UndefineOperationException();
}

bool Timer::timeOut() {
	if (type != COUNTDOWN) {
		throw DebugHelper::UndefineOperationException();
	}
	return timeCount >= timing;
}

int Timer::getTimeCount() {
	return timeCount;
}

int Timer::getTiming() {
	return timing;
}

void Timer::setFunc(function<void()> func) {
	this->func = func;
}
