#pragma once
#include "SceneBase.h"
#include <thread>

class SceneLoading : public SceneBase {
public:
	SceneLoading(int width, int height);
	void build() override;
	void start() override;
	void update() override;

private:
	enum LAYER {
		BACKGROUND = 0,
		UI = 50
	};
};