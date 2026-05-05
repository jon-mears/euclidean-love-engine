#include "angles.hpp"

#include <glm/glm.hpp>

Degrees::Degrees(float val) :
	mVal{ val }
{ }

Degrees::Degrees(Radians rad) :
	mVal{ glm::degrees<float>(rad) }
{ }

Degrees::operator float() const noexcept {
	return mVal;
}

Radians::Radians(float val) :
	mVal{ val }
{ }

Radians::Radians(Degrees deg) :
	mVal{ glm::radians<float>(deg) }
{ }

Radians::operator float() const noexcept {
	return mVal;
}

Degrees Deg(float deg) noexcept {
	return Degrees(deg);
}

Radians Rad(float rad) noexcept {
	return Radians(rad);
}

Radians Deg2Rad(Degrees deg) noexcept {
	return Radians(deg);
}

Degrees Rad2Deg(Radians rad) noexcept {
	return Degrees(rad);
}