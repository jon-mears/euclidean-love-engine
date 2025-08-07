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

TransformComponent::TransformComponent(GameObject* pGO) : Component{ pGO }, mWorldPosition{ 0 }, mLocalPosition{ 0 }, mEulerRotation{}, mScale{ 1 }, mQuatRotation{ 0.0f, 0.0f, 0.0f, 0.0f }
{
	mpObjectSpace = new Space(mLocalX, mLocalY, mLocalZ, mWorldPosition);
}

void TransformComponent::SetPosition(const glm::vec3& position, Space* pSpace) {
	mLocalPosition = position;
}

void TransformComponent::SetPosition(const glm::vec3& new_position,
	Space::Label eSpace) {
	switch (eSpace) {
	case Space::LOCAL:
		mLocalPosition = new_position;
		break;
	case Space::WORLD:
		if (!mpParent) mLocalPosition = new_position;
		else
		mLocalPosition = mpParent->GetSpace()->World2Space(
			new_position
		);
		break;
	case Space::OBJECT:
		mLocalPosition += new_position.x * mpObjectSpace->X() +
			new_position.y * mpObjectSpace->Y() +
			new_position.z * mpObjectSpace->Z();
		break;
	default:
		break;
	}
}

void TransformComponent::InterfaceMain() {

	enum RotationT {
		QUAT,
		EULER,
		ANGLE_AXIS
	};

	const char* options[] = {
		"Euler Angles",
		"Quaternion",
		"Angle Axis"
	};

	static int selection = 0;

	static Space::Label position_space = Space::LOCAL;
	static Space::Label rotation_space = Space::OBJECT_WORLD;
	static Space::Label scale_space = Space::OBJECT;

	glm::vec3 local_position = Position(position_space);
	glm::vec3 euler_rotation = EulerRotation();
	glm::vec3 scale = mScale;

	ImGui::Text("Position:");

	ImGui::Indent();

	if (ImGui::RadioButton("World", position_space == Space::WORLD)) position_space = Space::WORLD;

	ImGui::SameLine();

	if (ImGui::RadioButton("Local", position_space == Space::LOCAL)) position_space = Space::LOCAL;

	ImGui::SameLine();

	if (ImGui::RadioButton("Object", position_space == Space::OBJECT)) position_space = Space::OBJECT;

	if (ImGui::DragFloat3("##Position", glm::value_ptr(local_position))) {
		SetPosition(local_position, position_space);
	}

	ImGui::Unindent();

	ImGui::Text("Rotation:");

	ImGui::Indent();

	if (ImGui::BeginCombo("Format", options[selection])) {
		for (int i = 0; i < IM_ARRAYSIZE(options); ++i) {
			const bool is_selected = i == selection;
			if (ImGui::Selectable(options[i], is_selected)) {
				selection = i;
			}
		}

		ImGui::EndCombo();
	}

	if (ImGui::DragFloat3("##Rotation", glm::value_ptr(euler_rotation))) {
		SetEulerRotation(euler_rotation);
	}

	ImGui::Unindent();

	ImGui::Text("Scale:");

	ImGui::Indent();

	ImGui::DragFloat3("##Scale", glm::value_ptr(mScale));

	ImGui::Unindent();
}

void TransformComponent::Translate(const glm::vec3& translation, Space* pSpace) {
	glm::vec3 transl = translation.x * pSpace->X() + translation.y *
		pSpace->Y() + translation.z * pSpace->Z();

	mLocalPosition += transl;

	//for (auto child : mChildren) {
	//	child->Translate(transl);
	//}
}

void TransformComponent::SetEulerRotation(const glm::vec3& euler_rotation, 
	Space* pSpace) {
	if (pSpace == nullptr) { pSpace = GetSpace(); }

	mEulerRotation = euler_rotation.x * pSpace->X() + euler_rotation.y * pSpace->Y() +
		euler_rotation.z * pSpace->Z();

	mQuatDirty = true;
}

void TransformComponent::EulerRotate(const glm::vec3& rotation) {
	if (mEulerDirty) UpdateEulerRotation();

	mEulerRotation += rotation;
	mQuatDirty = true;
}

void TransformComponent::QuaternionRotate(const glm::quat& quaternion) {
	if (mQuatDirty) UpdateQuaternionRotation();

	mQuatRotation = quaternion * mQuatRotation;

	mEulerDirty = true;
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

void TransformComponent::SetScale(const glm::vec3& scale,
	Space::Label eSpace) {

	switch (eSpace) {
	case Space::OBJECT:
		mScale = scale;
	}
}

void TransformComponent::Scale(const glm::vec3& scale) {
	mScale += scale;
}

glm::vec3 TransformComponent::Position(Space::Label
eLabel) const {
	switch (eLabel) {
	case Space::LOCAL:
		return mLocalPosition;
	case Space::WORLD:
		if (!mpParent) return mLocalPosition;
		return mpParent->GetSpace()->Space2World(mLocalPosition);
	case Space::OBJECT:
		return glm::vec3{ 0 };
	default:
		return glm::vec3{ 0 };
	}
}

glm::vec3 TransformComponent::EulerRotation() {
	if (mEulerDirty) UpdateEulerRotation();
	return mEulerRotation;
}

glm::quat TransformComponent::QuatRotation() {
	if (mQuatDirty) UpdateQuaternionRotation();
	return mQuatRotation;
}

const glm::vec3& TransformComponent::Scale() const {
	return mScale;
}

void TransformComponent::SetQuaternionRotation(glm::quat const&
	quat_rotation) {
	mQuatRotation = quat_rotation;

	mEulerDirty = true;
}

glm::mat4 TransformComponent::ModelMatrix() {
	if (mbModelMatrixReady) {
		return mModel;
	}

	else {
		mModel = glm::mat4{ 1 };
		mModel = glm::translate(mModel, mLocalPosition);

		if (!mQuatDirty) {
			if (mpGO->Name() == "Box") std::cout << "quat" << std::endl;
			mModel = mModel * glm::toMat4(mQuatRotation);
		}
		else {
			if (mpGO->Name() == "Box") std::cout << "euler" << std::endl;
			glm::vec3 euler_rotation = EulerRotation();

			mModel = glm::rotate(mModel, glm::radians(euler_rotation.y),
				glm::vec3(0, 1, 0));
			mModel = glm::rotate(mModel, glm::radians(euler_rotation.x),
				glm::vec3(1, 0, 0));
			mModel = glm::rotate(mModel, glm::radians(euler_rotation.z),
				glm::vec3(0, 0, 1));
		}

		mModel = glm::scale(mModel, mScale);

		if (mpParent) {
			mModel = mpParent->ModelMatrix() * mModel;
		}

		mbModelMatrixReady = true;
		return mModel;
	}
}

void TransformComponent::Start() { }

void TransformComponent::Update() {  
	mbModelMatrixReady = false;
	mpObjectSpace->SetO(Position(Space::WORLD));
}

void TransformComponent::ConstUpdate() const { }

void TransformComponent::LookAt(const glm::vec3& crTarget) {
	glm::vec3 dir = glm::normalize(mLocalPosition - crTarget);
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

	mEulerDirty = false;
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

	mQuatDirty = false;
}

void TransformComponent::UpdateLocalAxes() {
	//glm::mat3 rotation_mat = glm::mat3(glm::yawPitchRoll(mEulerRotation.y, mEulerRotation.x, mEulerRotation.z));

	glm::mat3 rotation_mat = glm::toMat3(mQuatRotation);
	
	mLocalZ = glm::normalize(rotation_mat * glm::vec3(0, 0, 1));
	mLocalX = glm::normalize(rotation_mat * glm::vec3(1, 0, 0));
	mLocalY = glm::normalize(glm::cross(mLocalZ, mLocalX));

	mpObjectSpace->SetX(mLocalX);
	mpObjectSpace->SetY(mLocalY);
	mpObjectSpace->SetZ(mLocalZ);
}