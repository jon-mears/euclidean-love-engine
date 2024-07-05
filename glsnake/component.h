#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component {

private:
	virtual void interface();

protected:
	GameObject* mpGO;
public:
	virtual ~Component() { }

	virtual void Start() = 0;
	virtual void Update() = 0;

	template <typename C>
	C* GetComponent();

	Component(GameObject* pGO);

	friend class ObjectEditor; // to allow access to the component's
							   // interface
};

#include "component.tpp"
#endif