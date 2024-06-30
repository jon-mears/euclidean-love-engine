#include "targeted_camera.hpp"
#include "transform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// should the parent also be added to the component list?
TargetedCamera::TargetedCamera(GameObject* gameobject) : Camera(gameobject), mTarget{ 0.0f, 0.0f, 0.0f } { }

glm::mat4 TargetedCamera::view_matrix() {
	return glm::lookAt(mpTransform->position(), mTarget, glm::vec3{ 0.0f, 1.0f, 0.0f });
}