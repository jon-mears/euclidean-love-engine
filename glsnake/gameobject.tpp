#ifndef GAMEOBJECT_TPP
#define GAMEOBJECT_TPP

#include "gameobject.h"

#include <vector>

#include <algorithm>
#include <typeinfo>

class Component;

template <typename C>
C* GameObject::add() {
	C* c = new C(this);
	components.push_back(c);

	return c;
}

template <typename C>
void GameObject::erase() {
	std::vector<Component*>::iterator it = std::find_if(mOwnedComponents.begin(), mOwnedComponents.end(), [](Component* c) {
		return typeid(C) == typeid(*c);
		});

	if (it == mOwnedComponents.end()) return;

	delete* it;
	mOwnedComponents.erase(it);
}

template <typename C>
C* GameObject::retrieve() {
	std::vector<Component*>::iterator it = std::find_if(mAllComponents.begin(), mAllComponents.end(), [](Component* c) {
		return typeid(C) == typeid(*c);
		});

	if (it == mAllComponents.end()) return nullptr;

	return dynamic_cast<C*>(*it);
}

// COULD also use a share component, which just contains a 
// vector of component pointers... (eh, maybe not such a good idea)

// could also have a babygameobject...?

// the idea of allowing a single entity to have multiple of the same component
// doesn't seem TOO bad...

template <typename C>
C* GameObject::share(GameObject* pGO) {
	C* pComponent = pGO->retrieve<C>();
	mSharedComponents.push_back(pComponent);
	mAllComponents.push_back(pComponents);

	return pComponent;
}

template <typename C>
C* GameObject::retrieve_shared() {
	std::vector<Component*>::iterator it = std::find_if(mSharedComponents.begin(), mSharedComponents.end(), [](Component* c) {
		return typeid(C) == typeid(*c);
		});

	if (it == mSharedComponents.end()) return nullptr;

	return dynamic_cast<C*>(*it);
}

template <typename C>
C* GameObject::retrieve_owned() {
	std::vector<Component*>::iterator it = std::find_if(mOwnedComponents.begin(), mOwnedComponents.end(), [](Component* c) {
		return typeid(C) == typeid(*c);
		});

	if (it == mOwnedComponents.end()) return nullptr;

	return dynamic_cast<C*>(*it);
}

#endif