#include "Animation.h"
#include "Game.h"
#include "DebugHelper.h"

Animation::Animation(string animateName, int animateFrams, vec2 animateOffset, vec2 animateScaling, bool playOnce) : 
	frameTime(100), name(animateName), frames(animateFrams), offset(animateOffset), scaling(animateScaling), playOnce(playOnce) {
	time = 0;
	run = true;
	currentFrame = 0;
}

string Animation::getName() {
	return name;
}

int Animation::getFrames() {
	return frames;
}

int Animation::getCurrentFrame() {
	return currentFrame;
}

vec2 Animation::getOffset() {
	return offset;
}

vec2 Animation::getScaling() {
	return scaling;
}

void Animation::play() {
	run = true;
}

void Animation::replay() {
	currentFrame = 0;
	play();
}

void Animation::stop() {
	run = false;
}

void Animation::update() {
	if (run) {
		time += Game::getInstance()->getDeltaTime();
		if (time >= frameTime) {
			time = 0;
			if (playOnce && currentFrame + 1 == frames) {
				stop();
			} else {
				currentFrame = (currentFrame + 1) % frames;
			}
		}
	}
}

bool Animation::isPlaying() {
	return run;
}
