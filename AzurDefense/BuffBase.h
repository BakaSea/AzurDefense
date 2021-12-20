#pragma once
#include "GameObject.h"
#include "Timer.h"

class BuffBase : public GameObject {
public:
	BuffBase();
	BuffBase(int lasting);
	virtual ~BuffBase();
	void start() override;
	void update() override;
	void render() override;

protected:
	Timer* timer;
	virtual void init();
	virtual void startBuff();
	virtual void updateBuff();
	virtual void endBuff();
};