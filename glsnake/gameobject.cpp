#include "gameobject.h"
#include "component.h"
#include "game.h"
#include "window.hpp"

#include <string>
#include <vector>

GameObject::GameObject(std::string s) : Resource(s), mOwnedComponents(), mSharedComponents(), mAllComponents() { }
GameObject::GameObject() : Resource(), mOwnedComponents(), mSharedComponents(), mAllComponents() { }

void GameObject::Update() {
	for (Component* c : mOwnedComponents) {
		c->update();
	}
}

void GameObject::Start() {
	for (Component* c : mOwnedComponents) {
		c->start();
	}
}

void GameObject::ShareAll(GameObject* pGO) {
	for (std::vector<Component*>::iterator it = Begin<Component>(); it != End<Component>(); ++it) {
		mSharedComponents.push_back(*it);
		mAllComponents.push_back(*it);
	}
}