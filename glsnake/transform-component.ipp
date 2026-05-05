#ifndef TRANSFORM_COMPONENT_IPP
#define TRANSFORM_COMPONENT_IPP

#include "transform-component.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "angles.hpp"
#include "space.hpp"

//template <>
//glm::vec4 TransformComponent::AngleAxisRotation<Radians>(
//	Space const& space
//) noexcept
//{
//	MakeQuatClean();
//
//	glm::vec3 axis{ mQuatRotation.x, mQuatRotation.y, mQuatRotation.z };
//
//	axis = World2Space(Axis(axis), space);
//
//	return glm::vec4{ mQuatRotation.w, axis };
//}
//
//template <>
//glm::vec4 TransformComponent::AngleAxisRotation<Degrees>(
//	Space const& space
//) noexcept
//{
//	MakeQuatClean();
//
//	glm::vec3 axis{ mQuatRotation.x, mQuatRotation.y, mQuatRotation.z };
//
//	axis = World2Space(Axis(axis), space);
//
//	return glm::vec4{ Rad2Deg(Radians(mQuatRotation.w)), axis };
//}

//template <>
//glm::vec4 TransformComponent::AngleAxisRotation<Radians>(
//	Space::Label space
//) noexcept
//{
//	switch (space) {
//	case Space::OBJECT:
//		
//
//		break;
//	}
//}

#endif