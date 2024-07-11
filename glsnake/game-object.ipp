#ifndef GAME_OBJECT_IPP
#define GAME_OBJECT_IPP

#include "game-object.hpp"

#include <vector>

#include <algorithm>
#include <typeinfo>

class Component;

template <typename C>
C* GameObject::Add() {
	C* c = new C(this);
	mOwnedComponents.push_back(c);
	mAllComponents.push_back(c);

	return c;
}

template <typename C>
void GameObject::Erase() {
	std::vector<Component*>::iterator it = std::find_if(mOwnedComponents.begin(), mOwnedComponents.end(), [](Component* c) {
		return typeid(C) == typeid(*c);
		});

	if (it == mOwnedComponents.end()) return;

	delete* it;
	mOwnedComponents.erase(it);
}

template <typename C>
C* GameObject::Retrieve() {
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
C* GameObject::Share(GameObject* pGO) {
	C* pComponent = pGO->Retrieve<C>();
	mSharedComponents.push_back(pComponent);
	mAllComponents.push_back(pComponent);

	return pComponent;
}

template <typename C>
C* GameObject::RetrieveShared() {
	std::vector<Component*>::iterator it = std::find_if(mSharedComponents.begin(), mSharedComponents.end(), [](Component* c) {
		return typeid(C) == typeid(*c);
		});

	if (it == mSharedComponents.end()) return nullptr;

	return dynamic_cast<C*>(*it);
}

template <typename C>
C* GameObject::RetrieveOwned() {
	std::vector<Component*>::iterator it = std::find_if(mOwnedComponents.begin(), mOwnedComponents.end(), [](Component* c) {
		return typeid(C) == typeid(*c);
		});

	if (it == mOwnedComponents.end()) return nullptr;

	return dynamic_cast<C*>(*it);
}

#endif