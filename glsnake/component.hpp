#ifndef COMPONENT_HPP
#define COMPONENT_HPP

// every component MUST be associated to a GameObject!!!
// (this is fine because it is certainly allowed to make
// a GameObject with one component)

class GameObject;

#include <string>
#include <typeinfo>

class Component {
private:
	virtual void InterfaceHead();
	virtual void InterfaceMain();
	virtual void InterfaceTail();

protected:
	GameObject* mpGO;
	bool mbActive{ true };
public:
	virtual ~Component() { }

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void ConstUpdate() const = 0;

	template <typename C>	
	C* GetComponent();

	virtual const char* Name() const = 0;

	template <typename C>
	const C* GetComponent() const;

	Component(GameObject* pGO);

	inline bool IsActive() const { return mbActive; }
	inline void SetActive(bool bActive) { mbActive = bActive; }
	inline bool ToggleActive() { return mbActive = !mbActive; }

	inline GameObject* GO() { return mpGO; }

	virtual void Interface();
};

#include "component.ipp"
#endif