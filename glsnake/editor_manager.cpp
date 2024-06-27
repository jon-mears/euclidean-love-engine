#include "editor_manager.hpp"
#include "hierarchy_view.hpp"
#include "object_editor.hpp"
#include "ui_window.hpp"
#include <vector>

EditorManager& EditorManager::instance() {
	static EditorManager gEditorManager;
	return gEditorManager;
}

void EditorManager::startup() {
	mEditors.push_back(new HierarchyView());
	mEditors.push_back(new ObjectEditor());
}

void EditorManager::draw() {
	for (std::vector<UIWindow*>::iterator it = mEditors.begin(); it != mEditors.end(); ++it) {
		(*it)->draw();
	}
}

EditorManager::EditorManager() : mEditors(), mpSelected(NULL) { }