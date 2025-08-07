#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <iostream>
#include <vector>
#include <string>

#include "gizmo.hpp"
#include "resource.hpp"

class Component;
class App;

class GameObject : public Resource {
private:
	std::vector<Component*> mOwnedComponents;
	std::vector<Component*> mSharedComponents;
	std::vector<Component*> mAllComponents;

public:
	GameObject();

	template <typename C>
	C* Add();

	//template <>
	//NoGizmo* Add<NoGizmo>() {
	//	std::cout << "in nogizmo specialization" << std::endl;
	//	return nullptr;
	//}

	template <typename C>
	void Erase();

	template <typename C>
	C* Retrieve();

	template <typename C>
	C* Share(GameObject* pGO);

	void ShareAllFrom(GameObject* pGO);

	template <typename C>
	C* RetrieveShared();

	template <typename C>
	C* RetrieveOwned();

	void Update();
	void ConstUpdate() const;
	void Start();

	template <typename T> 
	std::vector<Component*>::iterator Begin() = delete;

	template <>
	std::vector<Component*>::iterator Begin<Component>() {
		return mAllComponents.begin();
	}

	template <typename T>
	std::vector<Component*>::iterator End() = delete;

	template <>
	std::vector<Component*>::iterator End<Component>() {
		return mAllComponents.end();
	}
};

#include "game-object.ipp"
#endif