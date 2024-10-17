#ifndef AABB_HPP
#define AABB_HPP

#include <glm/glm.hpp>

class AABB {
private:
	glm::vec3 mMin;
	glm::vec3 mMax;

public:
	AABB(glm::vec3 min, glm::vec3 max);
};
#endif