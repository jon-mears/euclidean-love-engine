#include "imgui.h"

#include "component.hpp"
#include "game-object.hpp"

Component::Component(GameObject* pGO) : mpGO(pGO) { }

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