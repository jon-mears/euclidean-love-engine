#include "perspective-component.hpp"
#include "game-object.hpp"
#include "projection-component.hpp"
#include "transform-component.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

PerspectiveComponent::PerspectiveComponent(GameObject* pGO) : ProjectionComponent{ pGO }, mFOVY{ 45.0f }, mAspect{ 0.0f }, mNear{ 0.01f }, mFar{ 100.0f } {

}

glm::mat4 PerspectiveComponent::ProjectionMatrix() {
	return glm::perspective(glm::radians(mFOVY), mAspect, mNear, mFar);
}