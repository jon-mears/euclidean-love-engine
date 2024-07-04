#include "editor_manager.hpp"
#include "hierarchy_view.hpp"
#include "object_editor.hpp"
#include "ui_window.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "game.h"
#include <vector>

EditorManager& EditorManager::instance() {
	static EditorManager gEditorManager;
	return gEditorManager;
}

void EditorManager::startup() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsLight();
	
	ImGui_ImplGlfw_InitForOpenGL(Game::instance().window(), true);
	ImGui_ImplOpenGL3_Init("#version 130");

	mEditors.push_back(new HierarchyView());
	mEditors.push_back(new ObjectEditor());
}

void EditorManager::draw() {
	for (std::vector<UIWindow*>::iterator it = mEditors.begin(); it != mEditors.end(); ++it) {
		(*it)->draw();
	}
}

EditorManager::EditorManager() : mEditors(), mpSelected(NULL) { }