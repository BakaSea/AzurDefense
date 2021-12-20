#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Animation.h"
#include "MathHelper.h"
using namespace std;
using namespace glm;

class GameObject {
public:
	GameObject();
	GameObject(const GameObject& A);
	virtual ~GameObject();
	virtual void start();
	virtual void update();
	virtual void render();
	virtual GameObject* createInstance();
	string getName();
	vec2 getSize();
	vec2 getBound();
	virtual bool inBound(vec3 point);
	void setScaling(vec2 scaling);
	vec2 getScaling();
	void enableAbsolutePosition();
	void disableAbsolutePosition();
	void enableAbsoluteRotation();
	void disableAbsoluteRotation();
	void enableAbsoluteScale();
	void disbaleAbsoluteScale();
	virtual void setPosition(vec3 position);
	virtual void setPosition(float x, float y, float z);
	void setRotation(float rotateX, float rotateY, float rotateZ);
	vec3 getPosition();
	float getRotateX();
	float getRotateY();
	float getRotateZ();
	void setLayer(int layer);
	int getLayer();
	vector<pair<string, int>> getAnimateInfo();
	bool hasAnimation();
	void setAnimation(string animateName);
	MathHelper::Plane getPlane();
	virtual void addChild(GameObject* object);
	virtual void removeChild(GameObject* object);
	vector<GameObject*> getChildList();
	void remove();
	
protected:
	string name;
	vec2 size, scaling;
	bool absPosition, absRotation, absScale;
	vec3 position;
	float rotateX, rotateY, rotateZ;
	vector<Animation*> animateList;
	Animation* currentAnimation;
	int layer;
	GameObject* parentObject;
	vector<GameObject*> childList;
	void startChild();
	void updateChild();
	void renderLowerChild();
	void renderUpperChild();
	void updateChildList();
};