#include "aabb.hpp"

#include <glm/glm.hpp>

AABB::AABB(glm::vec3 min, glm::vec3 max) : mMin(min), mMax(max) { }