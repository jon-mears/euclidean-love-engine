#ifndef COMPONENT_HPP
#define COMPONENT_HPP

class GameObject;

class Component {
private:
	virtual void Interface();

protected:
	GameObject* mpGO;
public:
	virtual ~Component() { }

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void ConstUpdate() const = 0;

	template <typename C>	
	C* GetComponent();

	template <typename C>
	const C* GetComponent() const;

	Component(GameObject* pGO);

	friend class ObjectEditor; // to allow access to the component's
							   // interface
};

#include "component.ipp"
#endif