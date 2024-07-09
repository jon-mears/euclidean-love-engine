#include "app.hpp"

#include <iostream>
#include <vector>
#include <utility>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera-component.hpp"
#include "game-object.hpp"
#include "resource.hpp"
#include "shader.hpp"
#include "mesh.hpp"
#include "game-object.hpp"
#include "scene.hpp"
#include "transform-component.hpp"
#include "resource-manager.hpp"
#include "ui-window.hpp"
#include "targeted-camera-component.hpp"

#include "object-editor.hpp"
#include "hierarchy-view.hpp"

#include "editor-manager.hpp"
#include "input-manager.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "key-mouse-input-service.hpp"
#include "render-engine.hpp"

App::App() : mInitScenes{}, mDeinitScenes{}, mpWindow(nullptr) { }

int App::Init() {	
	StartSystems();

	if (!mInitScenes.count(InitScene)) {
		std::cout << "error :: state with index " << static_cast<int>(InitScene) << " does not exist" << std::endl;
		std::exit(-1);
	}

	mInitScenes[InitScene](this);

	// iterate over gameobjects
	for (std::map<std::string, GameObject*>::iterator it = ResourceManager::Instance().Begin<GameObject>(); it != ResourceManager::Instance().End<GameObject>(); ++it) {
		GameObject* pGO = it->second;
		pGO->Start();
	}

	return 0;
}

void App::Loop() {
	while (!ShouldClose()) {

		// event polling
		InputManager::Instance().StartFrame();

		// imgui preparation
		EditorManager::Instance().StartFrame();

		// update gameobjects
		Update();

		// draw scene
		RenderEngine::Instance().Draw();
		
		// draw ui
		EditorManager::Instance().Draw();

		// imgui completion
		EditorManager::Instance().EndFrame();

		// swap buffers
		RenderEngine::Instance().EndFrame();
	}
}

void App::Update() {
	for (std::map<std::string, GameObject*>::iterator it = ResourceManager::Instance().Begin<GameObject>(); it != ResourceManager::Instance().End<GameObject>(); ++it) {
		GameObject* pGO = it->second;
		pGO->Update();
	}

	for (std::map<std::string, GameObject*>::iterator it = ResourceManager::Instance().
		Begin<GameObject>(); it != ResourceManager::Instance().End<GameObject>(); ++it) {
		GameObject* pGO = it->second;
		pGO->ConstUpdate();
	}
}

void App::Deinit() {
	for (std::map<std::string, GameObject*>::iterator it = ResourceManager::Instance().Begin<GameObject>(); it != ResourceManager::Instance().End<GameObject>(); ++it) {
		GameObject* pGO = it->second;
		delete pGO;
	}

	glfwTerminate();
}

void App::RegisterScene(Scene scene, SceneFunc init, SceneFunc deinit) {
	mInitScenes[scene] = init;
	mDeinitScenes[scene] = deinit;
}

GLFWwindow* App::Window() {
	return mpWindow;
}

bool App::ShouldClose() {

#ifdef _glfw3_h_
	return glfwWindowShouldClose(mpWindow);
#else
	return true;
#endif
}

void App::StartSystems() {

	// read a .cfg file to determine what subsystems to use???
	// kind of stuff that the application would need to be restarted 
	// to apply

	// Window *pWindow = new Window();
	// pWindow->mWidth = 600; pWindow->mHeight = 600; pWindow->title = "Engine";
	// RenderEngine::instance().provide_window(pWindow); 
	// (then, startup would ACTUALLY create the window, once graphics library init is done

	// Render Engine (should have its own list of gameobjects)
	//RenderEngine* pRenderEngine = new RenderEngine();

	RenderEngine::Instance().WindowInfo(600, 600, "Engine");
	RenderEngine::Instance().Startup();
	RenderEngine::Instance().EnableTests(Render::TEST_DEPTH);
	RenderEngine::Instance().EnableClears(Render::CLEAR_COLOR | Render::CLEAR_DEPTH);

	 mpWindow = RenderEngine::Instance().mpWindow;

	// pRenderEngine->startup(pWindow);

	// Resource Manager
	ResourceManager::Instance().Startup();

	// Editor Manager
	EditorManager::Instance().Startup();

	// Input Manager
	InputManager::Instance().ProvideService(new KeyMouseInputService());
	InputManager::Instance().ProvideWindow(mpWindow);
	InputManager::Instance().Startup();
}

App& App::Instance() {
	static App gApp;
	return gApp;
}