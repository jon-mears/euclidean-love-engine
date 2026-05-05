#include "space.hpp"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

Space Space::sWorld{
	glm::vec3{ 1.0f, 0.0f, 0.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f },
	glm::vec3{ 0.0f, 0.0f, 1.0f }, glm::vec3{ 0.0f }
};

bool Space::IsWorld(Space const& s) {
	return &s == &sWorld;
}

glm::vec3 Space2Space(
	glm::vec3 const& v, Space const& dest, Space const& src
)
{
	bool dest_is_world{ Space::IsWorld(dest) };
	bool src_is_world{ Space::IsWorld(src) };

	if (!dest_is_world) {
		if (!src_is_world) return dest.World2Space(src.Space2World(v));
		else return dest.World2Space(v);
	}
	else {
		if (!src_is_world) return src.Space2World(v);
		else return v;
	}
}

glm::vec3 Space2Space(
	Detail::Axis const& axis, Space const& dest, Space const& src
)
{
	bool dest_is_world{ Space::IsWorld(dest) };
	bool src_is_world{ Space::IsWorld(src) };

	if (!dest_is_world) {
		if (!src_is_world) return dest.World2Space(src.Space2World(axis));
		else return dest.World2Space(axis);
	}
	else {
		if (!src_is_world) return src.Space2World(axis);
		else return axis.ref;
	}
}

glm::vec3 World2Space(glm::vec3 const& v, Space const& dest) {
	return dest.World2SpaceMatrix() * (v - dest.O());
}

glm::vec3 World2Space(Detail::Axis const& axis, Space const& dest) {
	return dest.World2SpaceMatrix() * axis.ref;
}

glm::vec3 Space2World(glm::vec3 const& v, Space const& src) {
	return (src.Space2WorldMatrix() * v) + src.O();
}

glm::vec3 Space2World(Detail::Axis const& axis, Space const& src) {
	return src.Space2WorldMatrix() * axis.ref;
}

//glm::vec3 Space2Space(
//	glm::vec3 const& v, Space const& dest, Space const& src
//)
//{
//	return dest.World2Space(src.Space2World(v));
//}

Detail::Axis Axis(glm::vec3 const& v) {
	return Detail::Axis{ v };
}

std::ostream& operator<<(std::ostream& os, Space const& space) {
	os << "O: " << glm::to_string(space.mOrigin) << "\n" <<
		"X: " << glm::to_string(space.mBasis1) << "\n" <<
		"Y: " << glm::to_string(space.mBasis2) << "\n" <<
		"Z: " << glm::to_string(space.mBasis3);

	return os;
}