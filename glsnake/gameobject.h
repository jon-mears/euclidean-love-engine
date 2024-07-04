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
	std::vector<Component*> mOwnedComponents;
	std::vector<Component*> mSharedComponents;
	std::vector<Component*> mAllComponents;

public:
	GameObject(std::string);
	GameObject();

	template <typename C>
	C* add();

	template <typename C>
	void erase();

	template <typename C>
	C* Retrieve();

	template <typename C>
	C* Share(GameObject* pGO);

	template <typename C>
	C* RetrieveShared();

	template <typename C>
	C* RetrieveOwned();

	void update();
	void start();

	std::vector<Component*>::iterator component_begin();
	std::vector<Component*>::iterator component_end();
};

#include "gameobject.tpp"
#endif