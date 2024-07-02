#ifndef EDITOR_MANAGER_HPP
#define EDITOR_MANAGER_HPP

class GameObject;
class UIWindow;

#include <vector>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class EditorManager {
private:

	std::vector<UIWindow*> mEditors;

	void startup();
	void draw();

	EditorManager();

	EditorManager(EditorManager& lhs) = delete;
	EditorManager& operator=(EditorManager& lhs) = delete;
	EditorManager& operator=(EditorManager lhs) = delete;

public:
	GameObject* mpSelected;

	static EditorManager& instance();

	inline void start_frame() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	inline void end_frame() {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	friend class Game;
};
#endif