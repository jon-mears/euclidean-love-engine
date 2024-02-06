#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <algorithm>
#include <typeinfo>

#include "component.h"

class GameObject {
private:
	std::vector<Component*> components;

public:

	template <typename C>
	void add_component() {
		components.push_back(new C());
	}

	template <typename C>
	void remove_component() {
		auto it = find_if(components.begin(), components.end(), [](Component* c) {
				return typeid(C) == typeid(*c);
			});

		if (it == components.end()) return;

		delete* it;
		components.erase(it);
	}

	void start();
	void update() {
		for (Component* c : components) {
			c->update();
		}
	}
};
#endif