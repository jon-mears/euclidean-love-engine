#include "perspective.h"
#include "gameobject.h"
#include "projection.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Perspective::Perspective(GameObject* gameobject) : Projection(gameobject), fovy(0), aspect(0), near(0), far(0) { }

glm::mat4 Perspective::projection_matrix() {
	return glm::perspective(fovy, aspect, near, far);
}