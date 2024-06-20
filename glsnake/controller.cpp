#include "controller.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "subject.hpp"
#include "transform.h"
#include "game.h"
#include "gameobject.h"
#include "window.hpp"

void Controller::start() { }

void Controller::update() { 
	Transform* t = get_component<Transform>();

	if (t->window()->press(Key::W)) {
		t->translate(0.0f, 0.001f, 0.0f);
	}

	if (t->window()->press(Key::S)) {
		t->translate(0.0f, -0.001f, 0.0f);
	}
}

Controller::Controller(GameObject* gameobject) : Component(gameobject) { };