#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "component.h"
#include <glm/glm.hpp>

enum class Axis {
	X,
	Y,
	Z
};

class Transform : public Component {
private:
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 sc;
public:
	void set_posv(const glm::vec3& nPos) {
		pos = nPos;
	}

	void set_pos(const float x, const float y, const float z) {
		pos.x = x;
		pos.y = y;
		pos.z = z;
	}

	void translatev(const glm::vec3& trans) {
		pos += trans;
	}

	void translate(const float x, const float y, const float z) {
		pos.x += x;
		pos.y += y;
		pos.z += z;
	}

	void set_rotv(const glm::vec3& nRot) {
		rot = nRot;
	}

	void set_rot(const float x, const float y, const float z) {
		rot.x = x;
		rot.y = y;
		rot.z = z;
	}

	void rotatev(const glm::vec3& degs) {
		rot += degs;
	}

	void rotate(const float x, const float y, const float z) {
		rot.x += x;
		rot.y += y;
		rot.z += z;
	}

	void set_scalev(const glm::vec3& nSc) {
		sc = nSc;
	}

	void set_scale(const float x, const float y, const float z) {
		sc.x = x;
		sc.y = y;
		sc.z = z;
	}

	void scalev(const glm::vec3& rhs) {
		sc += rhs;
	}

	void scale(const float x, const float y, const float z) {
		sc.x += x;
		sc.y += y;
		sc.z += z;
	}
};

#endif