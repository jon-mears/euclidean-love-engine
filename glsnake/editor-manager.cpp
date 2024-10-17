#include "editor-manager.hpp"
#include "hierarchy-view.hpp"
#include "object-editor.hpp"
#include "ui-window.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "app.hpp"
#include <vector>

EditorManager& EditorManager::Instance() {
	static EditorManager gEditorManager;
	return gEditorManager;
}

void EditorManager::Startup() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsLight();
	
	ImGui_ImplGlfw_InitForOpenGL(App::Instance().Window(), true);
	ImGui_ImplOpenGL3_Init("#version 130");

	mEditors.push_back(new HierarchyView());
	mEditors.push_back(new ObjectEditor());
}

void EditorManager::Draw() {
	for (std::vector<UIWindow*>::iterator it = mEditors.begin(); it != mEditors.end(); ++it) {
		(*it)->Draw();
	}
}

EditorManager::EditorManager() : mEditors(), mpSelected(nullptr) { }