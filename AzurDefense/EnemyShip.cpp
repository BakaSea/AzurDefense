#include "EnemyShip.h"
#include "Game.h"
#include "ScenePlay.h"

EnemyShip::EnemyShip() {

}

bool EnemyShip::isDead() {
	return status == DEAD;
}

