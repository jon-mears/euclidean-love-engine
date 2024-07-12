#include "transform-component.hpp"
#include "game-object.hpp"
#include "component.hpp"
#include "imgui.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include "input-manager.hpp"
#include "math-3d.hpp"

TransformComponent::TransformComponent(GameObject* pGO) : Component{ pGO }, mPosition{}, mEulerRotation{}, mScale{ 1 }, mQuatRotation{ 0.0f, 0.0f, 0.0f, -1.0f }, mpWindow{ nullptr } { }

void TransformComponent::SetPosition(const glm::vec3& position) {
	mPosition = position;
}

void TransformComponent::Interface() {
	ImGui::InputFloat3("Position", glm::value_ptr(mPosition));
	ImGui::InputFloat3("Rotation", glm::value_ptr(mEulerRotation));
	ImGui::InputFloat3("Scale", glm::value_ptr(mScale));
}

void TransformComponent::SetPosition(const float x, const float y, const float z) {
	mPosition.x = x;
	mPosition.y = y;
	mPosition.z = z;
}

void TransformComponent::Translate(const glm::vec3& translation) {
	mPosition += translation;
}

void TransformComponent::Translate(const float x, const float y, const float z) {
	mPosition.x += x;
	mPosition.y += y;
	mPosition.z += z;
}

void TransformComponent::SetEulerRotation(const glm::vec3& euler_rotation) {
	mEulerRotation = euler_rotation;
}

void TransformComponent::SetEulerRotation(const float x, const float y, const float z) {
	mEulerRotation.x = x;
	mEulerRotation.y = y;
	mEulerRotation.z = z;
}

void TransformComponent::EulerRotate(const glm::vec3& rotation) {
	mEulerRotation += rotation;
}

void TransformComponent::EulerRotate(const float x, const float y, const float z) {
	mEulerRotation.x += x;
	mEulerRotation.y += y;
	mEulerRotation.z += z;
}

void TransformComponent::QuatRotate(const glm::quat quaternion) {
	mQuatRotation = quaternion * mQuatRotation;
}

// axis should be normalized
void TransformComponent::RotateAboutAxis(const glm::vec3& axis, const float deg) {
	const float rad = glm::radians(deg) / 2;
	const glm::quat quaternion = glm::quat(glm::cos(rad), glm::sin(rad) * axis);

	mQuatRotation = quaternion * mQuatRotation;
}

void TransformComponent::SetScale(const glm::vec3& scale) {
	mScale = scale;
}

void TransformComponent::SetScale(const float x, const float y, const float z) {
	mScale.x = x;
	mScale.y = y;
	mScale.z = z;
}

void TransformComponent::Scale(const glm::vec3& scale) {
	mScale += scale;
}

void TransformComponent::Scale(const float x, const float y, const float z) {
	mScale.x *= x;
	mScale.y *= y;
	mScale.z *= z;
}

const glm::vec3& TransformComponent::Position() const {
	return mPosition;
}

const glm::vec3& TransformComponent::EulerRotation() const {
	return mEulerRotation;
}

const glm::vec3& TransformComponent::Scale() const {
	return mScale;
}

glm::mat4 TransformComponent::ModelMatrix() {
	glm::mat4 model = glm::mat4{ 1 };
	model = glm::translate(model, mPosition);
	model = glm::rotate(model, glm::radians(mEulerRotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(mEulerRotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(mEulerRotation.z), glm::vec3(0, 0, 1));
	model = glm::scale(model, mScale);

	return model;
}

void TransformComponent::SetWindow(GLFWwindow *pWindow) {
	mpWindow = pWindow;
}

const GLFWwindow* TransformComponent::Window() const {
	return mpWindow;
}

void TransformComponent::Start() { }

void TransformComponent::Update() {  
	// update local axes (could potentially be placed in a separate component)

	glm::quat qLocalz = mQuatRotation * glm::quat{ 0.0f, 0.0f, 0.0f, -1.0f } * glm::quat{ mQuatRotation.w, -mQuatRotation.x, -mQuatRotation.y, -mQuatRotation.z };

	mLocalZ = glm::vec3{ qLocalz.x, qLocalz.y, qLocalz.z };
	mLocalX = glm::cross(-mLocalZ, glm::vec3{ 0.0f, 1.0f, 0.0f });
	mLocalY = glm::cross(-mLocalZ, mLocalX);

	if (InputManager::Instance().EventActive(Input::A_PRESSED)) {
		std::cout << glm::to_string(mLocalZ) << std::endl;
	}
}

void TransformComponent::ConstUpdate() const { }

void TransformComponent::LookAt(const glm::vec3& crTarget) {
	glm::vec3 dir = glm::normalize(mPosition - crTarget);
	glm::vec3 right = glm::cross(dir, glm::vec3{ 0.0f, 1.0f, 0.0f });
	glm::vec3 up = glm::cross(dir, right);

	/*
		[right.x   up.x   dir.x   0   ]
		[right.y   up.y   dir.y   0   ]
		[right.z   up.z   dir.z   0   ]
		[0         0      0       1   ]
	*/

	mQuatRotation = Math3D::Quaternion(right.x, up.x, dir.x, right.y, up.y, dir.y, right.z, up.z, dir.z);
}