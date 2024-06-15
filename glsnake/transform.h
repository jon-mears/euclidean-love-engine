#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "component.h"
#include <glm/glm.hpp>

class GameObject;

class Transform : public Component {
private:
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 sca;
public:
	Transform(GameObject* gameobject);
	void set_posv(const glm::vec3& nPos);
	void set_pos(const float x, const float y, const float z);
	void translatev(const glm::vec3& trans);
	void translate(const float x, const float y, const float z);
	void set_rotv(const glm::vec3& nRot);
	void set_rot(const float x, const float y, const float z);
	void rotatev(const glm::vec3& degs);
	void rotate(const float x, const float y, const float z);
	void set_scalev(const glm::vec3& nSca);
	void set_scale(const float x, const float y, const float z);
	void scalev(const glm::vec3& rhs);
	void scale(const float x, const float y, const float z);
	glm::vec3 position();
	glm::vec3 rotation();
	glm::vec3 scale();
	glm::mat4 model_matrix();
	virtual void start() override;
	virtual void update() override;
};

#endif