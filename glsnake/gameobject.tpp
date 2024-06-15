#ifndef GAMEOBJECT_TPP
#define GAMEOBJECT_TPP

#include "gameobject.h"

#include <vector>

#include <algorithm>
#include <typeinfo>

class Component;

template <typename C>
C* GameObject::add_component() {
	C* c = new C(this);
	components.push_back(c);

	return c;
}

template <typename C>
void GameObject::remove_component() {
	std::vector<Component*>::iterator it = std::find_if(components.begin(), components.end(), [](Component* c) {
		return typeid(C) == typeid(*c);
		});

	if (it == components.end()) return;

	delete* it;
	components.erase(it);
}

template <typename C>
C* GameObject::get_component() {
	std::vector<Component*>::iterator it = std::find_if(components.begin(), components.end(), [](Component* c) {
		return typeid(C) == typeid(*c);
		});

	if (it == components.end()) return nullptr;

	return dynamic_cast<C*>(*it);
}
#endif