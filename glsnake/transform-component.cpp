#include "transform-component.hpp"
#include "game-object.hpp"
#include "component.hpp"
#include "imgui.h"

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>
#include "input-manager.hpp"
#include "math-3d.hpp"

TransformComponent::TransformComponent(GameObject* pGO) : Component{ pGO }, mWorldPosition{ 0 }, mLocalPosition{ 0 }, mEulerRotation{}, mScale{ 1 }, mQuatRotation{ 0.0f, 0.0f, 0.0f, -1.0f }
{
	mpObjectSpace = new Space(mLocalX, mLocalY, mLocalZ, mWorldPosition);
}

void TransformComponent::SetPosition(const glm::vec3& position, Space* pSpace) {
	mWorldPosition = position.x * pSpace->X() + position.y * pSpace->Y() + 
		position.z * pSpace->Z() + pSpace->Origin();

	//std::cout << glm::to_string(mWorldPosition) << std::endl;
}

void TransformComponent::Interface() {
	ImGui::InputFloat3("Position", glm::value_ptr(mWorldPosition));
	ImGui::InputFloat3("Rotation", glm::value_ptr(mEulerRotation));
	ImGui::InputFloat3("Scale", glm::value_ptr(mScale));
}

void TransformComponent::Translate(const glm::vec3& translation, Space* pSpace) {
	mWorldPosition += translation.x * pSpace->X() + translation.y * pSpace->Y() +
		translation.z * pSpace->Z();
}

void TransformComponent::SetEulerRotation(const glm::vec3& euler_rotation, 
	Space* pSpace) {
	if (pSpace == nullptr) { pSpace = GetSpace(); }

	mEulerRotation = euler_rotation.x * pSpace->X() + euler_rotation.y * pSpace->Y() +
		euler_rotation.z * pSpace->Z();
}

void TransformComponent::EulerRotate(const glm::vec3& rotation) {
	mEulerRotation += rotation;
}

void TransformComponent::QuaternionRotate(const glm::quat& quaternion) {
	mQuatRotation = quaternion * mQuatRotation;
}
	
// axis should be normalized
void TransformComponent::RotateAboutAxis(const glm::vec3& axis, const float deg,
	const glm::vec3& rcOrigin) {
	const float rad = glm::radians(deg) / 2;
	const glm::quat quaternion = glm::quat(glm::cos(rad), glm::sin(rad) * axis);

	mQuatRotation = quaternion * mQuatRotation;

	const glm::mat3 vcRotationMatrix(quaternion);

	const glm::vec3 vcX = vcRotationMatrix * glm::vec3{ 1.0f, 0.0f, 0.0f };
	const glm::vec3 vcY = vcRotationMatrix * glm::vec3{ 0.0f, 1.0f, 0.0f };
	const glm::vec3 vcZ = vcRotationMatrix * glm::vec3{ 0.0f, 0.0f, 1.0f };
	Space* vpSpace = new Space(vcX, vcY, vcZ, rcOrigin);
	SetPosition(mWorldPosition, vpSpace);
}

void TransformComponent::SetScale(const glm::vec3& scale) {
	mScale = scale;
}

void TransformComponent::Scale(const glm::vec3& scale) {
	mScale += scale;
}

const glm::vec3& TransformComponent::Position() const {
	return mWorldPosition;
}

const glm::vec3& TransformComponent::EulerRotation() const {
	return mEulerRotation;
}

const glm::vec3& TransformComponent::Scale() const {
	return mScale;
}

void TransformComponent::SetQuaternionRotation(glm::quat const&
	quat_rotation) {
	mQuatRotation = quat_rotation;
}

glm::mat4 TransformComponent::ModelMatrix() {
	glm::mat4 model = glm::mat4{ 1 };
	model = glm::translate(model, mWorldPosition);
	model = glm::rotate(model, glm::radians(mEulerRotation.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(mEulerRotation.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(mEulerRotation.z), glm::vec3(0, 0, 1));
	model = glm::scale(model, mScale);
	
	return model;
}

void TransformComponent::Start() { }

void TransformComponent::Update() {  
	// update local axes
	//glm::quat qLocalz = mQuatRotation * glm::quat{ 0.0f, 0.0f, 0.0f, -1.0f } * glm::quat{ mQuatRotation.w, -mQuatRotation.x, -mQuatRotation.y, -mQuatRotation.z };

	//mLocalZ = glm::vec3{ qLocalz.x, qLocalz.y, qLocalz.z };
	//mLocalX = glm::cross(-mLocalZ, glm::vec3{ 0.0f, 1.0f, 0.0f });
	//mLocalY = glm::cross(-mLocalZ, mLocalX);

	//std::cout << glm::to_string(LocalZ()) << std::endl;
}

void TransformComponent::ConstUpdate() const { }

void TransformComponent::LookAt(const glm::vec3& crTarget) {
	glm::vec3 dir = glm::normalize(mWorldPosition - crTarget);
	glm::vec3 right = glm::cross(dir, glm::vec3{ 0.0f, 1.0f, 0.0f });
	glm::vec3 up = glm::cross(dir, right);

	/*
		[right.x   up.x   dir.x   0   ]
		[right.y   up.y   dir.y   0   ]
		[right.z   up.z   dir.z   0   ]
		[0         0      0       1   ]
	*/

	mQuatRotation = Math3D::Quaternion(right.x, up.x, dir.x, right.y, up.y, dir.y, right.z, up.z, dir.z);
	UpdateEulerRotation();
}

void TransformComponent::UpdateEulerRotation() {
	mEulerRotation = glm::eulerAngles(mQuatRotation);
}

void TransformComponent::UpdateQuaternionRotation() {
	glm::mat4 vMatrix;

	vMatrix = glm::rotate(vMatrix, mEulerRotation.y, glm::vec3{ 0.0f, 1.0f,
		0.0f });
	vMatrix = glm::rotate(vMatrix, mEulerRotation.x, glm::vec3{ 1.0f, 0.0f,
		0.0f });
	vMatrix = glm::rotate(vMatrix, mEulerRotation.z, glm::vec3{ 0.0f, 0.0f,
		1.0f });

	mQuatRotation.w = 0.5 * std::sqrt(std::max(0.0f,
		1 + vMatrix[0][0] + vMatrix[1][1] + vMatrix[2][2]));
	mQuatRotation.x = 0.5 * std::sqrt(std::max(0.0f,
		1 + vMatrix[0][0] - vMatrix[1][1] - vMatrix[2][2]));
	mQuatRotation.y = 0.5 * std::sqrt(std::max(0.0f,
		1 - vMatrix[0][0] + vMatrix[1][1] - vMatrix[2][2]));
	mQuatRotation.z = 0.5 * std::sqrt(std::max(0.0f,
		1 - vMatrix[0][0] - vMatrix[1][1] + vMatrix[2][2]));

	mQuatRotation.x = std::copysign(mQuatRotation.x, vMatrix[2][1] -
		vMatrix[1][2]);
	mQuatRotation.y = std::copysign(mQuatRotation.y, vMatrix[0][2] -
		vMatrix[2][0]);
	mQuatRotation.z = std::copysign(mQuatRotation.z, vMatrix[1][0] -
		vMatrix[0][1]);
}

void TransformComponent::UpdateLocalAxes() {
	//glm::mat3 rotation_mat = glm::mat3(glm::yawPitchRoll(mEulerRotation.y, mEulerRotation.x, mEulerRotation.z));

	glm::mat3 rotation_mat = glm::toMat3(mQuatRotation);
	
	mLocalZ = glm::normalize(rotation_mat * glm::vec3(0, 0, 1));
	mLocalX = glm::normalize(rotation_mat * glm::vec3(1, 0, 0));
	mLocalY = glm::normalize(glm::cross(mLocalZ, mLocalX));
}