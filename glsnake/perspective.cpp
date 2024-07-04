#include "perspective.h"
#include "gameobject.h"
#include "projection.h"
#include "transform.h"
#include "window.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Perspective::Perspective(GameObject* gameobject) : Projection(gameobject), fovy(45.0f), aspect(0), near(0.1f), far(100.0f) { 
	Transform* t = get_component<Transform>();

	aspect = 1;
}

glm::mat4 Perspective::projection_matrix() {
	return glm::perspective(glm::radians(fovy), aspect, near, far);
}