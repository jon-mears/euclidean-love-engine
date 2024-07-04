#include "game.h"

#include <iostream>
#include <vector>
#include <utility>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera.h"
#include "gameobject.h"
#include "resources.h"
#include "shader.h"
#include "mesh.h"
#include "gameobject.h"
#include "states.h"
#include "transform.h"
#include "resourcemanager.hpp"
#include "ui_window.hpp"
#include "targeted_camera.hpp"

#include "object_editor.hpp"
#include "hierarchy_view.hpp"

#include "editor_manager.hpp"
#include "input_manager.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "key_mouse_input_service.hpp"
#include "render_engine.hpp"

//int Game::glInit() {
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	for (std::pair<const std::string, Window*>& item : mWindows) {
//
//		Window* pWindow = item.second;
//		if (pWindow->() == -1) return -1;
//	}
//
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		return -1;
//	}
//
//	return 0;
//}

Game::Game() : init_states(), deinit_states(), mpWindow(NULL) { }

int Game::init() {	
	//if (glInit() == -1) return -1;
	start_systems();

	if (!init_states.count(Init_State)) {
		std::cout << "error :: state with index " << static_cast<int>(Init_State) << " does not exist" << std::endl;
		std::exit(-1);
	}

	init_states[Init_State](this);

	// iterate over gameobjects
	for (std::map<std::string, GameObject*>::iterator it = ResourceManager::instance().begin<GameObject>(); it != ResourceManager::instance().end<GameObject>(); ++it) {
		GameObject* go = it->second;
		go->start();
	}

	return 0;
}

void Game::loop() {
	while (!should_close()) {

		// event polling
		InputManager::instance().start_frame();

		// imgui preparation
		EditorManager::instance().start_frame();

		// update gameobjects
		update();

		// draw scene
		RenderEngine::instance().draw();
		
		// draw ui
		EditorManager::instance().draw();

		// imgui completion
		EditorManager::instance().end_frame();

		// swap buffers
		RenderEngine::instance().end_frame();
	}
}

void Game::update() {
	for (std::map<std::string, GameObject*>::iterator it = ResourceManager::instance().begin<GameObject>(); it != ResourceManager::instance().end<GameObject>(); ++it) {
		GameObject* go = it->second;
		go->update();
	}
}

//void Game::draw() {
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	Camera* c = nullptr;
//	for (std::map<std::string, GameObject*>::iterator it = ResourceManager::instance().begin<GameObject>(); it != ResourceManager::instance().end<GameObject>(); ++it) {
//		GameObject* go = it->second;
//		
//		if ((c = go->get_component<Camera>()) || (c = go->get_component<TargetedCamera>())) {
//			c->draw();
//		}
//	}
//
//	RenderEngine::instance().draw();
//	EditorManager::instance().draw();
//}

void Game::deinit() {
	for (std::map<std::string, GameObject*>::iterator it = ResourceManager::instance().begin<GameObject>(); it != ResourceManager::instance().end<GameObject>(); ++it) {
		GameObject* go = it->second;
		delete go;
	}

	glfwTerminate();
}

void Game::register_state(State s, StateFunc init, StateFunc deinit) {
	init_states[s] = init;
	deinit_states[s] = deinit;
}

GLFWwindow* Game::window() {
	return mpWindow;
}

bool Game::should_close() {
	//for (std::map<std::string, Window*>::iterator it = mWindows.begin(), it_next = it; it != mWindows.end(); it = it_next) {
	//	++it_next;

	//	Window* pWindow = it->second;
	//	if (pWindow->should_close()) mWindows.erase(it);
	//}

	//return !mWindows.size();

#ifdef _glfw3_h_
	return glfwWindowShouldClose(mpWindow);
#else
	return true;
#endif
}

void Game::start_systems() {

	// read a .cfg file to determine what subsystems to use???
	// kind of stuff that the application would need to be restarted 
	// to apply

	// Window *pWindow = new Window();
	// pWindow->mWidth = 600; pWindow->mHeight = 600; pWindow->title = "Engine";
	// RenderEngine::instance().provide_window(pWindow); 
	// (then, startup would ACTUALLY create the window, once graphics library init is done

	// Render Engine (should have its own list of gameobjects)
	//RenderEngine* pRenderEngine = new RenderEngine();

	RenderEngine::instance().window_info(600, 600, "Engine");
	RenderEngine::instance().startup();
	RenderEngine::instance().enable_tests(Render::TEST_DEPTH);
	RenderEngine::instance().enable_clears(Render::CLEAR_COLOR | Render::CLEAR_DEPTH);

	 mpWindow = RenderEngine::instance().mpWindow;

	// pRenderEngine->startup(pWindow);

	// Resource Manager
	ResourceManager::instance().startup();

	// Editor Manager
	EditorManager::instance().startup();

	// Input Manager
	InputManager::instance().provide_service(new KeyMouseInputService());
	InputManager::instance().provide_window(mpWindow);
	InputManager::instance().startup();
}

Game &Game::instance() {
	static Game gGame;
	return gGame;
}