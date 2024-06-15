#include "gameobject.h"
#include "component.h"
#include "game.h"

GameObject::GameObject(Game* game) : _game(game) { }

void GameObject::update() {
	for (Component* c : components) {
		c->update();
	}
}

Game* GameObject::game() {
	return _game;
}