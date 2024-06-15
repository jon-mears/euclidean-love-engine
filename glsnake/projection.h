#ifndef PROJECTION_H
#define PROJECTION_H

#include "component.h"

#include <glm/glm.hpp>

class GameObject;

class Projection : public Component {
public:
	Projection(GameObject* gameobject);
	virtual glm::mat4 projection_matrix() = 0;

	virtual void start() override;
	virtual void update() override;
};
#endif