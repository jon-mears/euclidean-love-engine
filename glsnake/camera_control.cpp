#include "camera_control.hpp"
#include "transform.h"
#include "component.h"
#include "gameobject.h"
#include "input_manager.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

CameraControl::CameraControl(GameObject* gameobject) : Component(gameobject), mpTransform(NULL) { }

void CameraControl::start() {
	mpTransform = get_component<Transform>();
}

void CameraControl::update() {
	if (InputManager::instance().event_active(Input::PANNING)) {
		float deltaX = InputManager::instance().relative_axis(Input::HORIZONTAL);
		float deltaY = InputManager::instance().relative_axis(Input::VERTICAL);

		mpTransform->translatev(deltaX * mpTransform->localx() + deltaY * mpTransform->localy());
	}
}