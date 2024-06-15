#include "controller.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "subject.hpp"
#include "transform.h"
#include "game.h"
#include "gameobject.h"

void Controller::start() { }

void Controller::update() { 
	Transform* t = get_component<Transform>();

	if (glfwGetKey(go->game()->window(), GLFW_KEY_W) == GLFW_PRESS) {
		t->translate(0.0f, 0.001f, 0.0f);
	}

	if (glfwGetKey(go->game()->window(), GLFW_KEY_A) == GLFW_PRESS) {
		t->translate(-0.001f, 0.0f, 0.0f);
	}

	if (glfwGetKey(go->game()->window(), GLFW_KEY_S) == GLFW_PRESS) {
		t->translate(0.0f, -0.001f, 0.0f);
	}

	if (glfwGetKey(go->game()->window(), GLFW_KEY_D) == GLFW_PRESS) {
		t->translate(0.001f, 0.0f, 0.0f);
	}
}

Controller::Controller(GameObject* gameobject) : Component(gameobject) { };