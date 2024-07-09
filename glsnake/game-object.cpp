#include "game-object.hpp"
#include "component.hpp"
#include "app.hpp"
#include "window.hpp"

#include <string>
#include <vector>

GameObject::GameObject() : mOwnedComponents{}, mSharedComponents{}, mAllComponents{} { }

void GameObject::Update() {
	for (Component* pComponent : mOwnedComponents) {
		pComponent->Update();
	}
}

void GameObject::ConstUpdate() const {
	for (Component* pComponent : mOwnedComponents) {
		pComponent->ConstUpdate();
	}
}

void GameObject::Start() {
	for (Component* pComponent : mOwnedComponents) {
		pComponent->Start();
	}
}

void GameObject::ShareAllFrom(GameObject* pGO) {
	for (std::vector<Component*>::iterator it = Begin<Component>(); it != End<Component>(); ++it) {
		mSharedComponents.push_back(*it);
		mAllComponents.push_back(*it);
	}
}