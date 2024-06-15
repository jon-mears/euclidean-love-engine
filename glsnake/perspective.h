#ifndef PERSPECTIVE_H
#define PERSPECTIVE_H

#include <glm/glm.hpp>
#include "projection.h"

class GameObject;

class Perspective : public Projection {
private:
	float fovy, aspect, near, far;

public:
	Perspective(GameObject* gameobject);
	virtual glm::mat4 projection_matrix() override;
};
#endif