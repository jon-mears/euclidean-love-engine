#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>

class Component;
class Game;

class GameObject {
private:
	std::vector<Component*> components;
	Game* _game;

public:
	GameObject(Game* game);

	template <typename C>
	C* add_component();

	template <typename C>
	void remove_component();

	template <typename C>
	C* get_component();

	void update();
	Game* game();
};

#include "gameobject.tpp"
#endif