#include "object-editor.hpp"
#include "imgui.h"

#include <vector>
#include "game-object.hpp"
#include "component.hpp"
#include "editor-manager.hpp"

ObjectEditor::ObjectEditor() : UIWindow() { }

void ObjectEditor::Draw() {

	GameObject *pSelected = EditorManager::Instance().mpSelected;

	ImGui::Begin("Object Viewer");

	if (pSelected == nullptr) {
		ImGui::Text("No Object Selected");
	}
	
	else {
		for (std::vector<Component*>::iterator it = pSelected->Begin<Component>(); it != pSelected->End<Component>(); ++it) {
			(*it)->Interface();
		}
	}

	ImGui::End();
}