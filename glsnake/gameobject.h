#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>

#include "resource.hpp"

class Component;
class Game;
class Window;

class GameObject : public Resource {
private:
	std::vector<Component*> components;

public:
	GameObject(std::string);
	GameObject();

	template <typename C>
	C* add_component();

	template <typename C>
	void remove_component();

	template <typename C>
	C* get_component();

	void update();
	void start();

	std::vector<Component*>::iterator component_begin();
	std::vector<Component*>::iterator component_end();
};

#include "gameobject.tpp"
#endif