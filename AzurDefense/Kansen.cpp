#include "Kansen.h"
#include "ScenePlay.h"
#include "Game.h"

Kansen::Kansen() {

}

void Kansen::createAircraft(AirCraft* aircraft, int acAtk, int acAirDef, int acHp, bool acBellicose, vec2 offset, int delay) {
	ScenePlay* scene = dynamic_cast<ScenePlay*>(Game::getInstance()->getSceneController()->getCurrentScene());
	if (scene != nullptr) {
		vec2 loc = getLocation() + offset;
		if (scene->isLegalLocation(loc)) {
			vec3 front = getFront();
			aircraft->setLayer(ScenePlay::CHARACTER + 1);
			aircraft->setRotation(scene->getMainCamera()->getPitch(), 0.0f, 0.0f);
			aircraft->setAttack(acAtk);
			aircraft->setAirDef(acAirDef);
			aircraft->setMaxHp(acHp);
			aircraft->setHp(acHp);
			aircraft->setBellicose(acBellicose);
			aircraft->setEnemy(isEnemy());
			aircraft->setFront(vec2(front.z, front.x));
			aircraft->setCharacter(true);
			Timer* t1 = new Timer(Timer::COUNTDOWN, delay, false, Timer::FUNCNULL);
			t1->setFunc([this, scene, aircraft, loc, t1] {
				scene->addObject(aircraft);
				scene->addCharacter(loc, aircraft);
				removeChild(t1);
				});
			addChild(t1);
		}
	}
}

void Kansen::attackEnemy() {
	if (currentAnimation->getCurrentFrame() == attackFrame) {
		if (!hasAttacked) {
			doAttack();
			hasAttacked = true;
		}
	} else {
		hasAttacked = false;
		if (currentAnimation->getCurrentFrame() == currentAnimation->getFrames() - 1) {
			attackCD->start();
		}
	}
}
