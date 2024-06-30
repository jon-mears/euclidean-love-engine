#include "transform.h"
#include "gameobject.h"
#include "component.h"
#include "imgui.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

Transform::Transform(GameObject* gameobject) : Component(gameobject), pos(), rot(), sca(1), mRotation(), mpWindow(NULL) { }

void Transform::set_posv(const glm::vec3& nPos) {
	pos = nPos;
}

void Transform::interface() {
	ImGui::InputFloat3("Position", glm::value_ptr(pos));
	ImGui::InputFloat3("Rotation", glm::value_ptr(rot));
	ImGui::InputFloat3("Scale", glm::value_ptr(sca));
}

void Transform::set_pos(const float x, const float y, const float z) {
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void Transform::translatev(const glm::vec3& trans) {
	pos += trans;
}

void Transform::translate(const float x, const float y, const float z) {
	pos.x += x;
	pos.y += y;
	pos.z += z;
}

void Transform::set_rotv(const glm::vec3& nRot) {
	rot = nRot;
}

void Transform::set_rot(const float x, const float y, const float z) {
	rot.x = x;
	rot.y = y;
	rot.z = z;
}

void Transform::rotatev(const glm::vec3& degs) {
	rot += degs;
}

void Transform::rotate(const float x, const float y, const float z) {
	rot.x += x;
	rot.y += y;
	rot.z += z;
}

void Transform::rotate(const glm::quat q) {
	mRotation = q * mRotation;
}

// axis should be normalized
void Transform::rotate(const glm::vec3 axis, const float deg) {

	const float rad = glm::radians(deg) / 2;
	const glm::quat q = glm::quat(glm::cos(rad), glm::sin(rad) * axis);

	mRotation = q * mRotation;


}

void Transform::set_scalev(const glm::vec3 &nSca) {
	sca = nSca;
}

void Transform::set_scale(const float x, const float y, const float z) {
	sca.x = x;
	sca.y = y;
	sca.z = z;
}

void Transform::scalev(const glm::vec3& rhs) {
	sca += rhs;
}

void Transform::scale(const float x, const float y, const float z) {
	sca.x *= x;
	sca.y *= y;
	sca.z *= z;
}

glm::vec3 &Transform::position() {
	return pos;
}

glm::vec3 Transform::rotation() {
	return rot;
}

glm::vec3 Transform::scale() {
	return sca;
}

glm::mat4 Transform::model_matrix() {
	glm::mat4 model = glm::mat4(1);
	model = glm::translate(model, pos);
	model = glm::rotate(model, glm::radians(rot.y), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(rot.x), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(rot.z), glm::vec3(0, 0, 1));
	model = glm::scale(model, sca);

	return model;
}

void Transform::set_window(Window *pWindow) {
	mpWindow = pWindow;
}

Window* Transform::window() {
	return mpWindow;
}

void Transform::start() { }

void Transform::update() {  
	// update local axes (could potentially be placed in a separate component)

	glm::quat qLocalz = mRotation * glm::quat{ 0.0f, 0.0f, 0.0f, -1.0f } * glm::quat{ mRotation.w, -mRotation.x, -mRotation.y, -mRotation.z };

	mLocalZ = glm::vec3{ qLocalz.x, qLocalz.y, qLocalz.z };
	mLocalX = glm::cross(-mLocalZ, glm::vec3{ 0.0f, 1.0f, 0.0f });
	mLocalY = glm::cross(-mLocalZ, mLocalX);
}