#include "camera-control-component.hpp"
#include "transform-component.hpp"
#include "component.hpp"
#include "game-object.hpp"
#include "input-manager.hpp"
#include "math-3d.hpp"
#include "targeted-camera-component.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

// intended for targeted cameras!
CameraControlComponent::CameraControlComponent(GameObject* pGO) : Component{ pGO }, mpTransform{nullptr}, mpTargetedCamera{nullptr}, mOrbitTarget{glm::vec3{0.0f, 0.0f, 0.0f}, 1.0f, 0.0f, 0.0f}, mLookTarget{0.0f, 0.0f} { }

void CameraControlComponent::Start() {
	mpTransform = GetComponent<TransformComponent>();
	mpTargetedCamera = GetComponent<TargetedCameraComponent>();

	if (mpTargetedCamera == nullptr) {
		std::cerr << "no targeted camera" << std::endl;
		std::exit(-1);
	}

}

void CameraControlComponent::Update() {
	if (InputManager::Instance().EventActive(Input::PANNING)) {
		float deltaX = -mXPanSpeed * InputManager::Instance().RelativeAxis(Input::HORIZONTAL);
		float deltaY = mYPanSpeed * InputManager::Instance().RelativeAxis(Input::VERTICAL);

		mpTransform->Translate(deltaX * mpTransform->LocalX() + deltaY * mpTransform->LocalY());
	}

	if (InputManager::Instance().EventActive(Input::ORBITING)) {
		float deltaX = -mXOrbitSpeed * InputManager::Instance().RelativeAxis(Input::HORIZONTAL);
		float deltaY = mYOrbitSpeed * InputManager::Instance().RelativeAxis(Input::VERTICAL);

		mOrbitTarget.latitude += deltaX;
		mOrbitTarget.longitude += deltaY;

		mpTransform->SetPosition(Math3D::SphericalCoordinates(mOrbitTarget.position, mOrbitTarget.latitude, mOrbitTarget.longitude, mOrbitTarget.distance));

		mpTargetedCamera->SetTarget(mOrbitTarget.position);
	}

	if (InputManager::Instance().EventActive(Input::LOOKING)) {
		float deltaX = -mXLookSpeed * InputManager::Instance().RelativeAxis(Input::HORIZONTAL);
		float deltaY = -mYLookSpeed * InputManager::Instance().RelativeAxis(Input::VERTICAL);
	}
}

void CameraControlComponent::ConstUpdate() const { }