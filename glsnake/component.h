#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component {

private:
	virtual void interface();

protected:
	GameObject* go;
public:
	virtual ~Component() = default;

	virtual void start() = 0;
	virtual void update() = 0;

	template <typename C>
	C* get_component();
	Component(GameObject* gameobject);

	friend class ObjectEditor; // to allow access to the component's
							   // interface
};

#include "component.tpp"
#endif