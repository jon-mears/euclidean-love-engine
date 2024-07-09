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

	void Startup();
	void Draw();

	EditorManager();

	EditorManager(EditorManager& lhs) = delete;
	EditorManager& operator=(EditorManager& lhs) = delete;
	EditorManager& operator=(EditorManager lhs) = delete;

public:
	GameObject* mpSelected;

	static EditorManager& Instance();

	inline void StartFrame() {
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	inline void EndFrame() {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	friend class App;
};
#endif