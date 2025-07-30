#include "game-object.hpp"
#include "gizmo.hpp"
#include "component.hpp"
#include "app.hpp"

#include <string>
#include <vector>

GameObject::GameObject() : Resource{}, mOwnedComponents {}, mSharedComponents{}, mAllComponents{} { }

void GameObject::Update() {
	for (Component* pComponent : mOwnedComponents) {
		if (pComponent->IsActive()) {
			pComponent->Update();
		}
	}
}

void GameObject::ConstUpdate() const {
	for (Component* pComponent : mOwnedComponents) {
		if (pComponent->IsActive()) {
			pComponent->ConstUpdate();
		}
	}
}

void GameObject::Start() {
	for (Component* pComponent : mOwnedComponents) {
		pComponent->Start();
	}
}

void GameObject::ShareAllFrom(GameObject* pGO) {
	for (std::vector<Component*>::iterator it = pGO->Begin<Component>(); it != pGO->End<Component>(); ++it) {
		mSharedComponents.push_back(*it);
		mAllComponents.push_back(*it);
	}
}

//template<>
//NoGizmo* GameObject::Add<NoGizmo>() {
//	return nullptr;
//}