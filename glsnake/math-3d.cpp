#include "math-3d.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace Math3D {
	glm::vec3 SphericalCoordinates(const glm::vec3 center, const float latitude, const float longitude, const float radius) {
		return glm::vec3{ radius * glm::sin(glm::radians(latitude)) * glm::cos(glm::radians(longitude)), radius * glm::sin(glm::radians(latitude)) * glm::sin(glm::radians(longitude)), radius * glm::cos(glm::radians(latitude)) };
	}

	glm::quat Quaternion(const float m00, const float m01, const float m02,
		const float m10, const float m11, const float m12, const float m20,
		const float m21, const float m22) {
		return glm::quat(glm::mat3{ m00, m01, m02, m10, m11, m12, m20, m21, m22 });
	}
}