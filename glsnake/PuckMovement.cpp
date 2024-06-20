#include "PuckMovement.hpp"
#include "gameobject.h"
#include "component.h"
#include "transform.h"

#include <glm/glm.hpp>
#include <iostream>

PuckMovement::PuckMovement(GameObject* gameobject) : Component(gameobject), dir(), speed() { }

void PuckMovement::start() {
	srand(25);
	dir.x = rand();
	srand(50);
	dir.y = rand();
	dir = glm::normalize(dir);
}

void PuckMovement::update() {
	Transform* t = get_component<Transform>();

	t->translatev(glm::vec3(speed * dir, 0.0f));

	glm::vec3 prev_pos = t->position();

	if (prev_pos.x > 1.0f) {
		t->set_pos(1.0f, prev_pos.y, prev_pos.z);
		dir.x = -dir.x;
	}

	if (prev_pos.x < -1.0f) {
		t->set_pos(-1.0f, prev_pos.y, prev_pos.z);
		dir.x = -dir.x;
	}

	prev_pos = t->position();

	if (prev_pos.y > 1.0f) {
		t->set_pos(prev_pos.x, 1.0f, prev_pos.z);
		dir.y = -dir.y;
	}

	if (prev_pos.y < -1.0f) {
		t->set_pos(prev_pos.x, -1.0f, prev_pos.z);
		dir.y = -dir.y;
	}
}