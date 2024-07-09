#include "hierarchy-view.hpp"
#include "resource-manager.hpp"
#include "imgui.h"
#include "editor-manager.hpp"

#include <map>

void HierarchyView::Draw() {
	ImGui::Begin("Hierarchy View");

	for (std::map<std::string, GameObject*>::iterator it = ResourceManager::Instance().Begin<GameObject>(); it != ResourceManager::Instance().End<GameObject>(); ++it) {

		if (ImGui::Button(it->first.c_str())) {
			EditorManager::Instance().mpSelected = it->second;
		}
	}

	ImGui::End();
}