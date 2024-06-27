#include "hierarchy_view.hpp"
#include "resourcemanager.hpp"
#include "imgui.h"
#include "editor_manager.hpp"

#include <map>

void HierarchyView::draw() {
	ImGui::Begin("Hierarchy View");

	for (std::map<std::string, GameObject*>::iterator it = ResourceManager::instance().begin<GameObject>(); it != ResourceManager::instance().end<GameObject>(); ++it) {

		if (ImGui::Button(it->first.c_str())) {
			EditorManager::instance().mpSelected = it->second;
		}
	}

	ImGui::End();
}