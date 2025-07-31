#ifndef SPACE_HPP
#define SPACE_HPP

#include <glm/glm.hpp>

class Space {
private:
	glm::vec3 mBasis1, mBasis2, mBasis3;
	glm::vec3 mOrigin;

public:

	enum Label {
		WORLD,
		LOCAL,
		OBJECT
	};

	inline glm::vec3 X() { return mBasis1; }
	inline glm::vec3 Y() { return mBasis2; }
	inline glm::vec3 Z() { return mBasis3; }
	inline glm::vec3 O() { return mOrigin; }
	inline glm::vec3 Origin() { return mOrigin; }

	inline void SetX(const glm::vec3& x) { mBasis1 = x; }
	inline void SetY(const glm::vec3& y) { mBasis2 = y; }
	inline void SetZ(const glm::vec3& z) { mBasis3 = z; }
	inline void SetO(const glm::vec3& o) { mOrigin = o; }

	Space(const glm::vec3& basis1, const glm::vec3& basis2,
		const glm::vec3& basis3, const glm::vec3& origin) :
		mBasis1{ basis1 }, mBasis2{ basis2 }, mBasis3{ basis3 },
		mOrigin{ origin } { }

	glm::mat3 World2SpaceMatrix() {
		return glm::mat3{
			mBasis1.x, mBasis2.x, mBasis3.x,
			mBasis1.y, mBasis2.y, mBasis3.y,
			mBasis1.z, mBasis2.z, mBasis3.z 
		};
	}

	glm::mat3 Space2WorldMatrix() {
		return glm::mat3{
			mBasis1.x, mBasis1.y, mBasis1.z,
			mBasis2.x, mBasis2.y, mBasis2.z,
			mBasis3.x, mBasis3.y, mBasis3.z 
		};
	}

	glm::vec3 World2Space(const glm::vec3& vrcVec) {
		return World2SpaceMatrix() * (vrcVec - mOrigin);
	}

	glm::vec3 Space2World(const glm::vec3& vrcVec) {
		return (Space2WorldMatrix() * vrcVec) + mOrigin;
	}

	static Space* World() {
		static Space* spWorldSpace{ nullptr };

		if (spWorldSpace == nullptr) {
			glm::vec3 x{ 1.0f, 0.0f, 0.0f };
			glm::vec3 y{ 0.0f, 1.0f, 0.0f };
			glm::vec3 z{ 0.0f, 0.0f, 1.0f };
			glm::vec3 o{ 0.0f, 0.0f, 0.0f };

			spWorldSpace = new Space(x, y, z, o);
		}
		return spWorldSpace;
	}
};
#endif