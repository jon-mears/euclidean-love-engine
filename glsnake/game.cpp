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

namespace {
	void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}
}	

int Game::glInit() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (_window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;

		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(_window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);

	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

	return 0;
}

int Game::init() {
	if (glInit() == -1) return -1;

	if (!init_states.count(Init_State)) {
		std::cout << "error :: state with index " << static_cast<int>(Init_State) << " does not exist" << std::endl;
		exit(-1);
	}

	init_states[Init_State](this);
	return 0;
}

void Game::process_input() {
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(_window, true);
	}

	//if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS) {
	//	GameObject* go = gameobject("Rectangle");
	//	Transform* t = go->get_component<Transform>();
	//	t->translate(0.0f, 0.001f, 0.0f);
	//}

	//if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS) {
	//	GameObject* go = gameobject("Rectangle");
	//	Transform* t = go->get_component<Transform>();
	//	t->translate(-0.001f, 0.0f, 0.0f);
	//}

	//if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS) {
	//	GameObject* go = gameobject("Rectangle");
	//	Transform* t = go->get_component<Transform>();
	//	t->translate(0.0f, -0.001f, 0.0f);
	//}

	//if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS) {
	//	GameObject* go = gameobject("Rectangle");
	//	Transform* t = go->get_component<Transform>();
	//	t->translate(0.001f, 0.0f, 0.0f);
	//}
}

void Game::loop() {
	while (!glfwWindowShouldClose(_window)) {
		process_input();
		update();
		draw();

		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
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

Shader* Game::add_shader(std::string name) {
	if (name == "")
		name = "shader_" + std::to_string(shaders.size() + 1);

	if (shaders.count(name))
		throw "a shader named " + name + " already exists.";

	shaders[name] = new Shader();
	return shaders[name];
}

Model* Game::add_model(std::string name) {
	if (name == "")
		name = "model_" + std::to_string(models.size() + 1);

	if (models.count(name))
		throw "a model named " + name + " already exists.";

	models[name] = new Model();
	return models[name];
}

GameObject* Game::add_gameobject(std::string name) {
	if (name == "")
		name = "object_" + std::to_string(gameobjects.size() + 1);

	if (gameobjects.count(name))
		throw "an object named " + name + " already exists";

	gameobjects[name] = new GameObject(this);
	return gameobjects[name];
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

GLFWwindow* Game::window() {
	return _window;
}

Game::Game(std::string t, int w, int h) : _window(nullptr), width(w), height(h), title(t), shaders(), models(), gameobjects() { }