#include "Character.h"
#include "Game.h"
#include "ScenePlay.h"
#include "DebugHelper.h"
#include "BuffAirDef.h"

Character::Character() {
	location = vec2(0.0f, 0.0f);
	armor = LIGHT;
	maxHp = hp = atk = airDef = maxBlock = 0;
	critRate = 0.05f;
	critDamage = 0.5f;
	atkImpRate = 0.0f;
	airDefImpRate = 0.0f;
	damagedImpRate = 0.0f;
	energy = 0;
	status = STAND;
	orientation = RIGHT;
	orientDegree = 0.0f;
	attackFrame = 0;
	deadFrame = 0;
	hasAttacked = false;
	attackCD = airDefCD = damagedTimer =  skillCD = nullptr;
	attackRange.clear();
	airDefRange.clear();
	enemyList.clear();
	aircraftList.clear();
}

Character::~Character() {
	location = vec2(0.0f, 0.0f);
	armor = LIGHT;
	maxHp = hp = atk = airDef = maxBlock = 0;
	critRate = 0.05f;
	critDamage = 0.5f;
	atkImpRate = 0.0f;
	airDefImpRate = 0.0f;
	energy = 0;
	status = STAND;
	orientation = RIGHT;
	orientDegree = 0.0f;
	attackFrame = 0;
	deadFrame = 0;
	hasAttacked = false;
	attackCD = airDefCD = damagedTimer = skillCD = nullptr;
	attackRange.clear();
	airDefRange.clear();
	enemyList.clear();
	aircraftList.clear();
}

void Character::start() {
	hp = maxHp;
}

void Character::render() {
	renderLowerChild();
	vec3 color = vec3(1.0f, 1.0f, 1.0f);
	if (damagedTimer != nullptr) {
		color = vec3(1.0f, 0.0f, 0.0f);
	}
	if (hasAnimation()) {
		vec4 offset(currentAnimation->getOffset(), 0.0f, 0.0f);
		mat4 model = MathHelper::getModelMatrix(getPosition(), getRotateX(), getRotateY(), getRotateZ(), getScaling(), vec2(1.0f, 1.0f));
		offset = model * offset;
		Game::getInstance()->getRenderer2D()->renderMixColor(
			Game::getInstance()->getResourceManager()->getTexture(name, currentAnimation->getName(), currentAnimation->getCurrentFrame()),
			color, getPosition() + vec3(offset), size, getRotateX(), getRotateY(), getRotateZ(), getScaling(), Renderer2D::BOTTOM);
	} else {
		Game::getInstance()->getRenderer2D()->renderMixColor(
			Game::getInstance()->getResourceManager()->getTexture(name), 
			color, getPosition(), size, getRotateX(), getRotateY(), getRotateZ(), getScaling(), Renderer2D::BOTTOM);
	}
	renderUpperChild();
}

GameObject* Character::createInstance() {
	return new Character();
}

vec2 Character::getLocation() {
	return location;
}

void Character::setLocation(vec2 location) {
	this->location = location;
}

void Character::setLocation(int x, int y) {
	setLocation(vec2(x, y));
}

bool Character::isEnemy() {
	return false;
}

Character::STATUS Character::getStatus() {
	return status;
}

void Character::setStatus(STATUS status) {
	this->status = status;
	string animateName;
	switch (status) {
	case DRAG: animateName = "Drag"; break;
	case STAND: animateName = "Stand"; break;
	case MOVE: animateName = "Move"; break;
	case ATTACK: animateName = "Attack"; break;
	case DEAD: animateName = "Dead"; break;
	case SKILL: animateName = "Skill"; break;
	}
	setAnimation(animateName);
}

Character::ORIENT Character::getOrient() {
	return orientation;
}

void Character::setOrient(ORIENT orient) {
	orientation = orient;
	switch (orient) {
	case RIGHT: {
		orientDegree = 0.0f;
		setRotation(rotateX, 0.0f, rotateZ);
		break;
	}
	case DOWN: {
		orientDegree = -90.0f;
		setRotation(rotateX, 0.0f, rotateZ);
		break;
	}
	case LEFT: {
		orientDegree = 180.0f;
		setRotation(rotateX, 180.0f, rotateZ);
		break;
	}
	case UP: {
		orientDegree = 90.0f;
		setRotation(rotateX, 180.0f, rotateZ);
		break;
	}
	}
}

void Character::getDamaged(float damage) {
	if (status != DRAG && status != DEAD) {
		hp -= (int)((1.0f + damagedImpRate) * damage);
		if (hp < 0) {
			hp = 0;
		}
		if (damagedTimer == nullptr) {
			addChild(damagedTimer = new Timer(Timer::COUNTDOWN, 500, false, [&] {
				Timer* t = damagedTimer;
				damagedTimer = nullptr;
				removeChild(t);
				}));
		}
	}
}

int Character::getHp() {
	return hp;
}

int Character::getMaxHp() {
	return maxHp;
}

int Character::getEnergy() {
	return energy;
}

vector<vec2> Character::getAttackRange() {
	return attackRange;
}

vector<vec2> Character::getAirDefRange() {
	return airDefRange;
}

int Character::getMaxBlock() {
	return maxBlock;
}

Character::ARMOR Character::getArmor() {
	return armor;
}

void Character::addHp(int hp) {
	this->hp += hp;
	if (this->hp > this->maxHp) {
		this->hp = this->maxHp;
	}
}

int Character::getAttack() {
	return (int)((1.0f + atkImpRate) * atk);
}

void Character::incAtkImpRate(float rate) {
	atkImpRate += rate;
}

void Character::decAtkImpRate(float rate) {
	atkImpRate -= rate;
}

int Character::getAirDef() {
	return (int)((1.0f + airDefImpRate) * airDef);
}

void Character::incAirDefImpRate(float rate) {
	airDefImpRate += rate;
}

void Character::decAirDefImpRate(float rate) {
	airDefImpRate -= rate;
}

Timer* Character::getSkillCD() {
	return skillCD;
}

vec3 Character::getFront() {
	switch (orientation) {
	case RIGHT: return vec3(1.0f, 0.0f, 0.0f);
	case DOWN: return vec3(0.0f, 0.0f, 1.0f);
	case LEFT: return vec3(-1.0f, 0.0f, 0.0f);
	case UP: return vec3(0.0f, 0.0f, -1.0f);
	}
	return vec3(0.0f, 0.0f, 0.0f);
}

void Character::createThrowingObject(ThrowingObject* obj, float angle, float velocity, float damage, int num, vec2 offset, vec2 scaling) {
	vec3 front = getFront();
	float startAngle = angle / 2.0f;
	if (num & 1) {
		ThrowingObject* t = dynamic_cast<ThrowingObject*>(obj->createInstance());
		t->setEnemy(isEnemy());
		t->setDamage(damage);
		t->disableGravity();
		t->aim(getPosition() + front * offset.x + vec3(0.0f, offset.y, 0.0f), front * velocity);
		t->setLayer(ScenePlay::CHARACTER);
		t->setRotation(Game::getInstance()->getSceneController()->getCurrentScene()->getMainCamera()->getPitch(), 0.0f, 0.0f);
		t->setScaling(scaling);
		Game::getInstance()->getSceneController()->getCurrentScene()->addObject(t);
		startAngle = angle;
		num--;
	}
	for (int i = 0; i < num / 2; ++i) {
		ThrowingObject* t = dynamic_cast<ThrowingObject*>(obj->createInstance());
		t->setEnemy(isEnemy());
		t->setDamage(damage);
		t->disableGravity();
		mat4 model(1.0f);
		model = MathHelper::getModelMatrix(vec3(0.0f), 0.0f, startAngle + angle * (float)i, 0.0f, vec2(1.0f, 1.0f), vec2(1.0f, 1.0f));
		vec4 v = model * vec4(front, 0.0f);
		t->aim(getPosition() + front * offset.x + vec3(0.0f, offset.y, 0.0f), v * velocity);
		t->setLayer(ScenePlay::CHARACTER);
		t->setRotation(Game::getInstance()->getSceneController()->getCurrentScene()->getMainCamera()->getPitch(), 0.0f, 0.0f);
		t->setScaling(scaling);
		Game::getInstance()->getSceneController()->getCurrentScene()->addObject(t);
	}
	for (int i = 0; i < num / 2; ++i) {
		ThrowingObject* t = dynamic_cast<ThrowingObject*>(obj->createInstance());
		t->setEnemy(isEnemy());
		t->setDamage(damage);
		t->disableGravity();
		mat4 model(1.0f);
		model = MathHelper::getModelMatrix(vec3(0.0f), 0.0f, -startAngle - angle * (float)i, 0.0f, vec2(1.0f, 1.0f), vec2(1.0f, 1.0f));
		vec4 v = model * vec4(front, 0.0f);
		t->aim(getPosition() + front * offset.x + vec3(0.0f, offset.y, 0.0f), v * velocity);
		t->setLayer(ScenePlay::CHARACTER);
		t->setRotation(Game::getInstance()->getSceneController()->getCurrentScene()->getMainCamera()->getPitch(), 0.0f, 0.0f);
		t->setScaling(scaling);
		Game::getInstance()->getSceneController()->getCurrentScene()->addObject(t);
	}
	delete obj;
}

void Character::createThrowingObject(ThrowingObject* obj, vec3 target, float radius, float time, float damage, int num, vec2 offset, vec2 scaling) {
	vec3 front = getFront();
	for (int i = 0; i < num; ++i) {
		ThrowingObject* t = dynamic_cast<ThrowingObject*>(obj->createInstance());
		t->setEnemy(isEnemy());
		t->setDamage(damage);
		vec2 point = radius * MathHelper::getRandomCirclePoint();
		target.x += point.x;
		target.z += point.y;
		t->aim(getPosition() + front * offset.x + vec3(0.0f, offset.y, 0.0f), target, time);
		t->setLayer(ScenePlay::CHARACTER);
		t->setRotation(Game::getInstance()->getSceneController()->getCurrentScene()->getMainCamera()->getPitch(), 0.0f, 0.0f);
		t->setScaling(scaling);
		Game::getInstance()->getSceneController()->getCurrentScene()->addObject(t);
	}
	delete obj;
}

bool Character::hasAirCraftInRange() {
	aircraftList.clear();
	ScenePlay* scene = dynamic_cast<ScenePlay*>(Game::getInstance()->getSceneController()->getCurrentScene());
	if (scene != nullptr) {
		for (vec2& range : airDefRange) {
			mat4 model = MathHelper::getModelMatrix(vec3(0.0f), 0.0f, 0.0f, orientDegree, vec2(1.0f, 1.0f), vec2(1.0f, 1.0f));
			vec4 point(range, 0.0f, 0.0f);
			point = model * point;
			vec2 loc(point);
			auto aircrafts = scene->getAirCraftList(getLocation() + loc);
			for (AirCraft* aircraft : aircrafts) {
				if (aircraft->isEnemy() ^ isEnemy()) {
					aircraftList.emplace_back(aircraft);
				}
			}
		}
	}
	return !aircraftList.empty();
}

bool Character::hasEnemyInRange() {
	enemyList.clear();
	return !enemyList.empty();
}

void Character::attackAirCraft() {
	for (Character* aircraft : aircraftList) {
		aircraft->getDamaged(calculateDamage(aircraft));
	}
	airDefCD->start();
	BuffAirDef* buf = new BuffAirDef();
	buf->setLayer(1);
	addChild(buf);
}

void Character::attackEnemy() {
	
}

void Character::doAttack() {
	for (Character* enemy : enemyList) {
		enemy->getDamaged(calculateDamage(enemy));
	}
}

float Character::calculateDamage(GameObject* object) {
	float p = float(rand()) / float(RAND_MAX);
	float damage = getAttack();
	if (dynamic_cast<AirCraft*>(object)) {
		damage = getAirDef();
	}
	if (p <= critRate) {
		damage += (float)getAttack() * critDamage;
	}
	return damage;
}

bool Character::isDead() {
	return currentAnimation->getCurrentFrame() == deadFrame;
}

void Character::doSkill() {

}

void Character::useSkill() {
	if (skillCD->timeOut()) {
		setStatus(SKILL);
		Game::getInstance()->getSoundEngine()->play2D(Game::getInstance()->getResourceManager()->getSound(name + "/Skill"));
		doSkill();
		skillCD->start();
	}
}

void Character::incDamagedImpRate(float rate) {
	damagedImpRate += rate;
}

void Character::decDamagedImpRate(float rate) {
	damagedImpRate -= rate;
}
