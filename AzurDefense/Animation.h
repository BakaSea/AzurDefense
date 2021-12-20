#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
using namespace std;
using namespace glm;

class Animation {
public:
	Animation(string animateName, int animateFrams, vec2 animateOffset = vec2(1.0f, 1.0f), vec2 animateScale = vec2(1.0f, 1.0f), bool playOnce = false);
	string getName();
	int getFrames();
	int getCurrentFrame();
	vec2 getOffset();
	vec2 getScaling();
	void play();
	void replay();
	void stop();
	void update();
	bool isPlaying();

private:
	const float frameTime;
	string name;
	int frames, time, currentFrame;
	vec2 offset, scaling;
	bool run, playOnce;
};
