#include "targeted-camera-component.hpp"
#include "transform-component.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// should the parent also be added to the component list?
TargetedCameraComponent::TargetedCameraComponent(GameObject* pGO) : CameraComponent{pGO}, mTarget{0.0f, 0.0f, 0.0f} { }

glm::mat4 TargetedCameraComponent::ViewMatrix() {
	return glm::lookAt(mpTransform->Position(), mTarget, glm::vec3{ 0.0f, 1.0f, 0.0f });
}