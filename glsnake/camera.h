#ifndef CAMERA_H
#define CAMERA_H
#include "component.h"
#include <glm/glm.hpp>

#include <vector>

class Transform;
class GameObject;

class Camera : public Component {
private:
	std::vector<GameObject*> viewables;

protected:
	Transform* mpTransform;

public:
	void start() override;
	void update() override;
	Camera(GameObject* gameobject);

	void add_viewable(GameObject* go);
	void draw();

	virtual glm::mat4 view_matrix();
};
#endif