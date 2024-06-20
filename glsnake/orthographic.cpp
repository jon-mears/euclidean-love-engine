#include "orthographic.h"
#include "gameobject.h"
#include "projection.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Orthographic::Orthographic(GameObject* gameobject) : Projection(gameobject), left(-1), right(1), bottom(-1), top(1) { }

glm::mat4 Orthographic::projection_matrix() {
	return glm::ortho(left, right, bottom, top);
}