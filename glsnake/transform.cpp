#include "transform.h"
#include "gameobject.h"
#include "component.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Transform::Transform(GameObject* gameobject) : Component(gameobject), pos(), rot(), sca(1), mpWindow(NULL) { }

void Transform::set_posv(const glm::vec3& nPos) {
	pos = nPos;
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
void Transform::update() { }