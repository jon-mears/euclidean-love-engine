#include "component.hpp"

#include "imgui.h"

class GameObject;

Component::Component(GameObject* GO) :
	mpGO{ GO }, mIsActive{ true }
{ }

Component::~Component() { }

bool Component::IsActive() const noexcept {
	return mIsActive;
}

void Component::SetActive(bool active) noexcept {
	mIsActive = active;
}

bool Component::ToggleActive() noexcept {
	return mIsActive = !mIsActive;
}

GameObject* Component::GO() noexcept {
	return mpGO;
}

void Component::Interface() { 
	InterfaceHead();
	InterfaceMain();
	InterfaceTail();
}

void Component::InterfaceHead() {
	ImGui::TextColored(ImVec4(0.0f,0.0f,1.0f,1.0f), Name());
}

void Component::InterfaceMain() { }

void Component::InterfaceTail() {
	ImGui::Separator();
}