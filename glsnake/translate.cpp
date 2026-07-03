#include "translate.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Translate::Translate() : mTranslation{ 0 } { };

void Translate::Set(glm::vec3 const& translation) {
	mTranslation = translation;

	mChangeCount++;
}
glm::vec3 Translate::Get() {
	return mTranslation;
}

void Translate::SetX(float x) {
	mTranslation.x = x;

	mChangeCount++;
}
float Translate::GetX() {
	return mTranslation.x;
}

void Translate::SetY(float y) {
	mTranslation.y = y;

	mChangeCount++;
}
float Translate::GetY() {
	return mTranslation.y;
}

void Translate::SetZ(float z) {
	mTranslation.z = z;

	mChangeCount++;
}
float Translate::GetZ() {
	return mTranslation.z;
}

glm::mat4 Translate::ApplyToRHSOf(glm::mat4 const& lhs) {
	return glm::translate(lhs, mTranslation);
}