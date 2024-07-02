#ifndef MATH_3D_HPP
#define MATH_3D_HPP

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Math3D {
	glm::vec3 spherical_coordinates(const glm::vec3 center, const float latitude, const float longitude, const float radius);

	glm::quat quaternion(const float m00, const float m01, const float m02,
		const float m10, const float m11, const float m12, const float m20,
		const float m21, const float m22);
}

#endif