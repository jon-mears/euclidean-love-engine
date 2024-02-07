#ifndef COMPONENT_H
#define COMPONENT_H

#include "gameobject.h"

class Component {

private:
	GameObject* go;
public:
	virtual ~Component();

	virtual void start() = 0;
	virtual void update() = 0;

	template <typename C>
	Component* get_component() {
		return go->get_component<C>();
	}

	Component(GameObject* go) : go(go) { }
};

#endif