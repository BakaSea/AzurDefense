	#pragma once
#include "GameObject.h"
#include <functional>
using namespace std;

class Timer : public GameObject {
public:
	enum TYPE {
		INTERVAL,
		COUNTDOWN
	};
	static void FUNCNULL();
	Timer(TYPE type, int timing, bool timeOutFirst, function<void()> func);
	void start() override;
	void update() override;
	void render() override;
	void addChild(GameObject* object) override;
	void removeChild(GameObject* object) override;
	bool timeOut();
	int getTimeCount();
	int getTiming();
	void setFunc(function<void()> func);

private:
	TYPE type;
	bool timeOutFirst, firstStart, firstOut;
	int timeCount, timing;
	function<void()> func;
};

