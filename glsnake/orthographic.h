#ifndef ORTHOGRAPHIC_H
#define ORTHOGRAPHIC_H

#include <glm/glm.hpp>

#include "projection.h"

class GameObject;

class Orthographic : public Projection {
public:
	float left, right, bottom, top;
public:

	Orthographic(GameObject* gameobject);
	virtual glm::mat4 projection_matrix() override;
};
#endif