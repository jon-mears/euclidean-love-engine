#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "projection.hpp"

glm::mat4 Orthographic::ProjectionMatrix() {
	return glm::ortho(mLeft, mRight, mBottom, mTop);
}