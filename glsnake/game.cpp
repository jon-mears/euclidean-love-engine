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
#include "model.h"
#include "gameobject.h"
#include "states.h"
#include "transform.h"
#include "window.hpp"
#include "resourcemanager.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

int Game::glInit() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	for (std::pair<const std::string, Window*>& item : mWindows) {

		Window* pWindow = item.second;
		if (pWindow->glInit() == -1) return -1;
	}

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	return 0;
}

int Game::init() {	
	if (glInit() == -1) return -1;

	start_systems();

	if (!init_states.count(Init_State)) {
		std::cout << "error :: state with index " << static_cast<int>(Init_State) << " does not exist" << std::endl;
		exit(-1);
	}

	init_states[Init_State](this);

	for (std::pair<const std::string, GameObject*>& item : gameobjects) {
		GameObject* go = item.second;
		go->start();
	}

	return 0;
}

void Game::loop() {
	while (!should_close()) {
		poll_events();

		imgui_start();

		update();
		draw();

		imgui_end();

		swap_buffers();
	}
}

void Game::imgui_start() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Game::imgui_end() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Game::update() {
	for (std::pair<const std::string, GameObject*>& item : gameobjects) {
		GameObject* go = item.second;
		go->update();
	}
}

void Game::draw() {
	glClear(GL_COLOR_BUFFER_BIT);

	Camera* c = nullptr;
	for (std::pair<const std::string, GameObject*>& item : gameobjects) {
		GameObject* go = item.second;
		
		if (c = go->get_component<Camera>()) {
			c->draw();
		}
	}
}

void Game::deinit() {
	for (std::pair<const std::string, GameObject*>& item : gameobjects) {
		GameObject* go = item.second;
		delete go;
	}

	glfwTerminate();
}

void Game::register_state(State s, StateFunc init, StateFunc deinit) {
	init_states[s] = init;
	deinit_states[s] = deinit;
}

void Game::add_shader(Shader* pShader) {
	std::string& name = pShader->name();
	
	if (name == "")
		name = "shader";

	if (shaders.count(name)) {
		int num = 1;
		size_t num_idx = name.size() + 1;

		name = name + "_" + std::to_string(num);
		while (shaders.count(name)) {
			++num;

			name = name.replace(num_idx, name.size() - num_idx, std::to_string(num));
		}
	}

	shaders[name] = pShader;
}

void Game::add_model(Model* pModel) {
	std::string& name = pModel->name();

	if (name == "")
		name = "model";

	if (models.count(name)) {
		int num = 1;
		size_t num_idx = name.size() + 1;

		name = name + "_" + std::to_string(num);
		while (models.count(name)) {
			++num;

			name = name.replace(num_idx, name.size() - num_idx, std::to_string(num));
		}
	}

	models[name] = pModel;
}

void Game::add_window(Window* pWindow) {
	mWindows[pWindow->title()] = pWindow;
}

void Game::add_gameobject(GameObject* pGameObject) {
	std::string& name = pGameObject->name();

	if (name == "")
		name = "gameobject";

	if (gameobjects.count(name)) {
		int num = 1;
		size_t num_idx = name.size() + 1;

		name = name + "_" + std::to_string(num);
		while (gameobjects.count(name)) {
			++num;

			name = name.replace(num_idx, name.size() - num_idx, std::to_string(num));
		}
	}

	gameobjects[name] = pGameObject;
}

Shader* Game::shader(const std::string& name) {
	return shaders[name];
}

Model* Game::model(const std::string& name) {
	return models[name];
}

GameObject* Game::gameobject(const std::string& name) {
	return gameobjects[name];
}

Window* Game::window(const std::string& name) {
	return mWindows[name];
}

Game::Game() : shaders(), models(), gameobjects(), mWindows() { }

bool Game::should_close() {
	for (std::map<std::string, Window*>::iterator it = mWindows.begin(), it_next = it; it != mWindows.end(); it = it_next) {
		++it_next;

		Window* pWindow = it->second;
		if (pWindow->should_close()) mWindows.erase(it);
	}

	return !mWindows.size();
}

void Game::swap_buffers() {
	for (std::pair<const std::string, Window*>& item : mWindows) {
		Window* pWindow = item.second;
		pWindow->swap_buffers();
	}
}

void Game::poll_events() {
	glfwPollEvents();
}

void Game::start_systems() {
	mpResourceManager = new ResourceManager();
	mpResourceManager->startup();
}

Game *Game::instance() {
	static Game* game = new Game();
	return game;
}

ResourceManager& Game::resource_manager() {
	return *mpResourceManager;
}