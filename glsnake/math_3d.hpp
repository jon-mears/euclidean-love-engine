#ifndef MATH_3D_HPP
#define MATH_3D_HPP

#include <glm/glm.hpp>
#include <cmath>

namespace Math3D {
	glm::vec3 spherical_coordinates(const glm::vec3 center, const float latitude, const float longitude, const float radius) {
		return glm::vec3{ radius * glm::sin(glm::radians(latitude)) * glm::cos(glm::radians(longitude)), radius * glm::sin(glm::radians(latitude)) * glm::sin(glm::radians(longitude)), radius * glm::cos(glm::radians(latitude)) };
	}
}

#endif