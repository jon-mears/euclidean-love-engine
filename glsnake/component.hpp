#ifndef COMPONENT_HPP
#define COMPONENT_HPP

class GameObject;

class Component {
private:
	virtual void Interface();

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

	template <typename C>
	const C* GetComponent() const;

	Component(GameObject* pGO);

	inline bool IsActive() { return mbActive; }
	inline void SetActive(bool bActive) { mbActive = bActive; }
	inline bool ToggleActive() { return mbActive = !mbActive; }

	friend class ObjectEditor; // to allow access to the component's
							   // interface
};

#include "component.ipp"
#endif