#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component {
protected:
	GameObject* go;
public:
	virtual ~Component() = default;

	virtual void start() = 0;
	virtual void update() = 0;

	template <typename C>
	C* get_component();
	Component(GameObject* gameobject);
};

#include "component.tpp"
#endif