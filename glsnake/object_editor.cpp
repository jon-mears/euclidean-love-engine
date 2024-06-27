#include "object_editor.hpp"
#include "imgui.h"

#include <vector>
#include "gameobject.h"
#include "component.h"
#include "editor_manager.hpp"

ObjectEditor::ObjectEditor() : UIWindow() { }

void ObjectEditor::draw() {

	GameObject *pSelected = EditorManager::instance().mpSelected;

	ImGui::Begin("Object Viewer");

	if (pSelected == NULL) {
		ImGui::Text("No Object Selected");
	}
	
	else {
		ImGui::Text(pSelected->name().c_str());

		for (std::vector<Component*>::iterator it = pSelected->component_begin(); it != pSelected->component_end(); ++it) {
			(*it)->interface();
		}
	}

	ImGui::End();
}