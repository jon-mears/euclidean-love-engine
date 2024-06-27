#include "gameobject.h"
#include "component.h"
#include "game.h"
#include "window.hpp"

#include <string>
#include <vector>

GameObject::GameObject(std::string s) : Resource(s), components() { }
GameObject::GameObject() : Resource(), components() { }

void GameObject::update() {
	for (Component* c : components) {
		c->update();
	}
}

void GameObject::start() {
	for (Component* c : components) {
		c->start();
	}
}

std::vector<Component*>::iterator GameObject::component_begin() {
	return components.begin();
}

std::vector<Component*>::iterator GameObject::component_end() {
	return components.end();
}