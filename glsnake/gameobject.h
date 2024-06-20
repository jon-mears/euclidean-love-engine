#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>

class Component;
class Game;
class Window;

class GameObject {
private:
	std::vector<Component*> components;
	std::string mName;

public:
	GameObject();

	template <typename C>
	C* add_component();

	template <typename C>
	void remove_component();

	template <typename C>
	C* get_component();

	void update();
	void start();

	std::string& name();
	void name(const std::string &name);
};

#include "gameobject.tpp"
#endif