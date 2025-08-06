#ifndef COMPONENT_HPP
#define COMPONENT_HPP

class GameObject;

class Component {
public:
	Component(GameObject* pGO);
	virtual ~Component();

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void ConstUpdate() const = 0;

	virtual char const* Name() const = 0;

	template <typename C>
	C* Get();

	template <typename C>
	C const* Get() const;

	bool IsActive() const noexcept;
	void SetActive(bool active) noexcept;
	bool ToggleActive() noexcept;

	GameObject* GO() noexcept;

	void Interface();

protected:
	GameObject* mpGO;
	bool mIsActive;

private:
	void InterfaceHead();
	virtual void InterfaceMain();
	void InterfaceTail();
};

#include "component.ipp"
#endif