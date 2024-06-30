#include "camera_control.hpp"
#include "transform.h"
#include "component.h"
#include "gameobject.h"
#include "input_manager.hpp"
#include "math_3d.hpp"
#include "targeted_camera.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

// intended for targeted cameras!
CameraControl::CameraControl(GameObject* gameobject) : Component(gameobject), mpTransform(NULL), mpTargetedCamera(NULL), mOrbitTarget{ glm::vec3{0.0f, 0.0f, 0.0f}, 1.0f, 0.0f, 0.0f }, mLookTarget{ 0.0f, 0.0f } { }

void CameraControl::start() {
	mpTransform = get_component<Transform>();
	mpTargetedCamera = get_component<TargetedCamera>();

	if (mpTargetedCamera == NULL) {
		std::cout << "no targeted camera" << std::endl;
	}

}

void CameraControl::update() {
	if (InputManager::instance().event_active(Input::PANNING)) {
		std::cout << "panning" << std::endl;
		float deltaX = -mXPanSpeed * InputManager::instance().relative_axis(Input::HORIZONTAL);
		float deltaY = mYPanSpeed * InputManager::instance().relative_axis(Input::VERTICAL);

		mpTransform->translatev(deltaX * mpTransform->localx() + deltaY * mpTransform->localy());
	}

	if (InputManager::instance().event_active(Input::ORBITING)) {
		std::cout << "orbiting" << std::endl;
		float deltaX = -mXOrbitSpeed * InputManager::instance().relative_axis(Input::HORIZONTAL);
		float deltaY = mYOrbitSpeed * InputManager::instance().relative_axis(Input::VERTICAL);

		mOrbitTarget.latitude += deltaX;
		mOrbitTarget.longitude += deltaY;

		mpTransform->set_posv(Math3D::spherical_coordinates(mOrbitTarget.position, mOrbitTarget.latitude, mOrbitTarget.longitude, mOrbitTarget.distance));

		std::cout << mpTargetedCamera->target().x << std::endl;
		mpTargetedCamera->set_target(mOrbitTarget.position);

		//else {
		//	/*glm::vec3 axis = deltaX * mpTransform->localx() + deltaY * mpTransform->localy();
		//	glm::vec3 unit_axis = glm::normalize(axis);*/

		//	mpTargetedCamera->set_target()
		//}
	}

	if (InputManager::instance().event_active(Input::LOOKING)) {
		std::cout << "looking" << std::endl;
		float deltaX = -mXLookSpeed * InputManager::instance().relative_axis(Input::HORIZONTAL);
		float deltaY = -mYLookSpeed * InputManager::instance().relative_axis(Input::VERTICAL);


	}
}