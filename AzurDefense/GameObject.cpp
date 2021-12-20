#include "GameObject.h"
#include <algorithm>
#include "Animation.h"
#include "DebugHelper.h"
#include "Game.h"
#include "MathHelper.h"

GameObject::GameObject() {
	name = "";
	size = vec2(0.0f, 0.0f);
	scaling = vec2(1.0f, 1.0f);
	absPosition = absRotation = false;
	position = vec3(0.0f, 0.0f, 0.0f);
	rotateX = rotateY = rotateZ = 0.0f;
	currentAnimation = nullptr;
	layer = 0;
	parentObject = nullptr;
	childList.clear();
}

GameObject::GameObject(const GameObject& A) {
	name = A.name;
	size = A.size;
	scaling = A.scaling;
	position = A.position;
	rotateX = A.rotateX;
	rotateY = A.rotateY;
	rotateZ = A.rotateZ;
	animateList.resize(A.animateList.size());
	for (int i = 0; i < animateList.size(); ++i) {
		animateList[i] = new Animation(*A.animateList[i]);
		if (A.currentAnimation == A.animateList[i]) {
			currentAnimation = animateList[i];
		}
	}
	layer = A.layer;
	parentObject = A.parentObject;
	childList.resize(A.childList.size());
	for (int i = 0; i < childList.size(); ++i) {
		childList[i] = new GameObject(*A.childList[i]);
	}
}

GameObject::~GameObject() {
	currentAnimation = nullptr;
	for (Animation*& animate : animateList) {
		delete animate;
		animate = nullptr;
	}
	animateList.clear();
	parentObject = nullptr;
	for (GameObject*& obj : childList) {
		delete obj;
		obj = nullptr;
	}
	childList.clear();
}

void GameObject::start() {
	startChild();
}

void GameObject::update() {
	updateChild();
	if (hasAnimation()) {
		currentAnimation->update();
	}
}

void GameObject::render() {
	renderLowerChild();
	if (hasAnimation()) {
		vec4 offset(currentAnimation->getOffset(), 0.0f, 0.0f);
		mat4 model = MathHelper::getModelMatrix(getPosition(), getRotateX(), getRotateY(), getRotateZ(), size, getScaling());
		offset = model * offset;
		Game::getInstance()->getRenderer2D()->render(
			Game::getInstance()->getResourceManager()->getTexture(name, currentAnimation->getName(), currentAnimation->getCurrentFrame()),
			getPosition() + vec3(offset), size, getRotateX(), getRotateY(), getRotateZ(), getScaling(), Renderer2D::MIDDLE);
	} else {
		Game::getInstance()->getRenderer2D()->render(
			Game::getInstance()->getResourceManager()->getTexture(name),
			getPosition(), size, getRotateX(), getRotateY(), getRotateZ(), getScaling(), Renderer2D::MIDDLE);
	}
	renderUpperChild();
}

GameObject* GameObject::createInstance() {
	return new GameObject();
}

string GameObject::getName() {
	return name;
}

vec2 GameObject::getSize() {
	return size;
}

vec2 GameObject::getBound() {
	return size / 2.0f;
}

bool GameObject::inBound(vec3 point) {
	vec4 p(point, 1.0f);
	mat4 model = MathHelper::getModelMatrix(getPosition(), getRotateX(), getRotateY(), getRotateZ(), size, getScaling());
	p = inverse(model) * p;
	return abs(p.x) <= 0.5f && abs(p.y) <= 0.5f;
}

void GameObject::setScaling(vec2 scaling) {
	this->scaling = scaling;
}

vec2 GameObject::getScaling() {
	if (!absScale && parentObject != nullptr) {
		return parentObject->getScaling() * scaling;
	} else {
		return scaling;
	}
}

void GameObject::enableAbsolutePosition() {
	absPosition = true;
}

void GameObject::disableAbsolutePosition() {
	absPosition = false;
}

void GameObject::enableAbsoluteRotation() {
	absRotation = true;
}

void GameObject::disableAbsoluteRotation() {
	absRotation = false;
}

void GameObject::enableAbsoluteScale() {
	absScale = true;
}

void GameObject::disbaleAbsoluteScale() {
	absScale = false;
}

void GameObject::setPosition(vec3 position) {
	this->position = position;
}

void GameObject::setPosition(float x, float y, float z) {
	setPosition(vec3(x, y, z));
}

void GameObject::setRotation(float rotateX, float rotateY, float rotateZ) {
	this->rotateX = rotateX;
	this->rotateY = rotateY;
	this->rotateZ = rotateZ;
}

vec3 GameObject::getPosition() {
	if (!absPosition && parentObject != nullptr) {
		return parentObject->getPosition() + position;
	} else {
		return position;
	}
}

float GameObject::getRotateX() {
	if (!absRotation && parentObject != nullptr) {
		return parentObject->getRotateX() + rotateX;
	} else {
		return rotateX;
	}
}

float GameObject::getRotateY() {
	if (!absRotation && parentObject != nullptr) {
		return parentObject->getRotateY() + rotateY;
	} else {
		return rotateY;
	}
}

float GameObject::getRotateZ() {
	if (!absRotation && parentObject != nullptr) {
		return parentObject->getRotateZ() + rotateZ;
	} else {
		return rotateZ;
	}
}

void GameObject::setLayer(int layer) {
	this->layer = layer;
}

int GameObject::getLayer() {
	if (parentObject != nullptr) {
		return parentObject->getLayer() + layer;
	} else {
		return layer;
	}
}

vector<pair<string, int>> GameObject::getAnimateInfo() {
	vector<pair<string, int>> result;
	for (Animation* animate : animateList) {
		result.emplace_back(pair<string, int>(animate->getName(), animate->getFrames()));
	}
	return result;
}

bool GameObject::hasAnimation() {
	return !animateList.empty();
}

void GameObject::setAnimation(string animateName) {
	currentAnimation->stop();
	for (int i = 0; i < animateList.size(); ++i) {
		if (animateList[i]->getName() == animateName) {
			animateList[i]->replay();
			currentAnimation = animateList[i];
			setScaling(animateList[i]->getScaling());
			return;
		}
	}
}

MathHelper::Plane GameObject::getPlane() {
	MathHelper::Plane plane = MathHelper::Plane(0.0f, 0.0f, 1.0f, 0.0f);
	plane = MathHelper::getModelMatrix(getPosition(), getRotateX(), getRotateY(), getRotateZ(), size, getScaling()) * plane;
	return plane;
}

void GameObject::addChild(GameObject* object) {
	object->parentObject = this;
	childList.emplace_back(object);
	object->start();
}

void GameObject::removeChild(GameObject* object) {
	for (GameObject*& child : childList) {
		if (child == object) {
			delete child;
			child = nullptr;
			break;
		}
	}
}

vector<GameObject*> GameObject::getChildList() {
	return childList;
}

void GameObject::remove() {
	if (parentObject != nullptr) {
		parentObject->removeChild(this);
	} else {
		delete this;
	}
}

void GameObject::startChild() {
	for (int i = 0; i < childList.size(); ++i) {
		if (childList[i] != nullptr) {
			childList[i]->start();
		}
	}
	updateChildList();
}

void GameObject::updateChild() {
	for (int i = 0; i < childList.size(); ++i) {
		if (childList[i] != nullptr) {
			if (DebugHelper::debug)
				DebugHelper::logInfo(childList[i]->getName());
			childList[i]->update();
		}
	}
	updateChildList();
}

void GameObject::renderLowerChild() {
	updateChildList();
	vector<GameObject*> lowerChilds;
	for (GameObject* obj : childList) {
		if (obj->getLayer() <= getLayer()) {
			lowerChilds.emplace_back(obj);
		}
	}
	sort(lowerChilds.begin(), lowerChilds.end(), [](GameObject* A, GameObject* B)->int {
		if (A->getLayer() != B->getLayer()) {
			return A->getLayer() < B->getLayer();
		}
		return A->getPosition().z < B->getPosition().z;
		});
	for (int i = 0; i < lowerChilds.size(); ++i) {
		if (lowerChilds[i] != nullptr) {
			lowerChilds[i]->render();
		}
	}
	updateChildList();
}

void GameObject::renderUpperChild() {
	updateChildList();
	vector<GameObject*> upperChilds;
	for (GameObject* obj : childList) {
		if (obj->getLayer() > getLayer()) {
			upperChilds.emplace_back(obj);
		}
	}
	sort(upperChilds.begin(), upperChilds.end(), [](GameObject* A, GameObject* B)->int {
		if (A->getLayer() != B->getLayer()) {
			return A->getLayer() < B->getLayer();
		}
		return A->getPosition().z < B->getPosition().z;
		});
	for (int i = 0; i < upperChilds.size(); ++i) {
		if (upperChilds[i] != nullptr) {
			upperChilds[i]->render();
		}
	}
	updateChildList();
}

void GameObject::updateChildList() {
	for (auto iter = childList.begin(); iter != childList.end();) {
		if (*iter == nullptr) {
			iter = childList.erase(iter);
		} else {
			++iter;
		}
	}
}
