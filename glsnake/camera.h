#ifndef CAMERA_H
#define CAMERA_H
#include "component.h"
#include <glm/glm.hpp>

#include <vector>

class GameObject;

class Camera : public Component {
private:
	std::vector<GameObject*> viewables;

public:
	void start() override;
	void update() override;
	Camera(GameObject* gameobject);

	void add_viewable(GameObject* go);
	void draw();

	glm::mat4 view_matrix();
};
#endif