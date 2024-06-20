#ifndef PUCKMOVEMENT_HPP
#define PUCKMOVEMENT_HPP

#include "component.h"
#include <glm/glm.hpp>

class GameObject;

class PuckMovement : public Component {
public:
	PuckMovement(GameObject* gameobject);
	virtual void start() override;
	virtual void update() override;

	glm::vec2 dir;
	float speed;
};
#endif