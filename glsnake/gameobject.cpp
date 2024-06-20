#include "gameobject.h"
#include "component.h"
#include "game.h"
#include "window.hpp"

#include <string>

GameObject::GameObject() : components(), mName("") { }

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

std::string& GameObject::name() {
	return mName;
}

void GameObject::name(const std::string& name) {
	mName = name;
}