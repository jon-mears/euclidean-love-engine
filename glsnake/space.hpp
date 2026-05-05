#ifndef SPACE_HPP
#define SPACE_HPP

#include <iostream>

#include <glm/glm.hpp>

namespace Detail {

	// Axis is effectively just an alias for glm::vec3, but should (or must)
	// be used whenever the position of the tail of the vector is determined by
	// by the called function. For example, the rotation functions (implicitly) 
	// set the tail to be the position of the rotated object, so that the axis
	// of rotation extends to infinity from the position of the object. Really
	// it's whenever a glm::vec3 should be considered a line rather than a
	// point. In particular, the axis is always considered as emanating from
	// the origin of whatever space you're in, so that if you convert from one
	// space to another, you should think of the axis as following the old
	// origin to the new origin. So an axis should be considered as a fixed
	// part of the basis gizmo for the purposes of visualizing a
	// change of basis versus a transformation. Should, for example, create an
	// add axis function for the purposes of visualization.
	struct Axis {
		glm::vec3 const& ref;
	};
}

class Space {
private:
	glm::vec3 mBasis1, mBasis2, mBasis3;
	glm::vec3 mOrigin;

public:

	enum Label {
		OBJECT,
		LOCAL,
		WORLD,

		OBJECT_WORLD // origin from object, axes from world
	};

	inline glm::vec3 X() const { return mBasis1; }
	inline glm::vec3 Y() const { return mBasis2; }
	inline glm::vec3 Z() const { return mBasis3; }
	inline glm::vec3 O() const { return mOrigin; }
	inline glm::vec3 Origin() const { return mOrigin; }

	inline void SetX(const glm::vec3& x) { mBasis1 = x; }
	inline void SetY(const glm::vec3& y) { mBasis2 = y; }
	inline void SetZ(const glm::vec3& z) { mBasis3 = z; }
	inline void SetO(const glm::vec3& o) { mOrigin = o; }

	Space() :
		mBasis1{ 1.0f, 0.0f, 0.0f }, mBasis2{ 0.0f, 1.0f, 0.0f },
		mBasis3{ 0.0f, 0.0f, 1.0f }, mOrigin{ 0.0f }
	{ }

	Space(const glm::vec3& basis1, const glm::vec3& basis2,
		const glm::vec3& basis3, const glm::vec3& origin) :
		mBasis1{ basis1 }, mBasis2{ basis2 }, mBasis3{ basis3 },
		mOrigin{ origin } { }

	glm::mat3 World2SpaceMatrix() const {
		return glm::mat3{
			mBasis1.x, mBasis2.x, mBasis3.x,
			mBasis1.y, mBasis2.y, mBasis3.y,
			mBasis1.z, mBasis2.z, mBasis3.z
		};
	}

	glm::mat3 Space2WorldMatrix() const {
		return glm::mat3{
			mBasis1.x, mBasis1.y, mBasis1.z,
			mBasis2.x, mBasis2.y, mBasis2.z,
			mBasis3.x, mBasis3.y, mBasis3.z
		};
	}

	glm::vec3 World2Space(const glm::vec3& vrcVec) const {
		return World2SpaceMatrix() * (vrcVec - mOrigin);
	}

	glm::vec3 World2Space(Detail::Axis const& axis) const {
		return World2SpaceMatrix() * axis.ref;
	}

	glm::vec3 Space2World(const glm::vec3& vrcVec) const {
		return (Space2WorldMatrix() * vrcVec) + mOrigin;
	}

	glm::vec3 Space2World(const Detail::Axis const& axis) const {
		return Space2WorldMatrix() * axis.ref;
	}

	static Space const& World() {
		return sWorld;
	}

	friend std::ostream& operator<<(std::ostream& os, Space const& space);

	static bool IsWorld(Space const& s);

private:
	static Space sWorld;
};

glm::vec3 Space2Space(
	glm::vec3 const& v, Space const& dest, Space const& src
);

glm::vec3 Space2Space(
	Detail::Axis const& axis, Space const& dest, Space const& src
);

glm::vec3 World2Space(glm::vec3 const& v, Space const& dest);
glm::vec3 World2Space(Detail::Axis const& axis, Space const& dest);
glm::vec3 Space2World(glm::vec3 const& v, Space const& src);
glm::vec3 Space2World(Detail::Axis const& axis, Space const& src);

Detail::Axis Axis(glm::vec3 const& v);

#endif