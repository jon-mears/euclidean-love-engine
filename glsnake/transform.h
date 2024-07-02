#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "component.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class GameObject;
class Window;
class GLFWwindow;

class Transform : public Component {
private:
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 sca;

	// should be a normalized quaternion
	glm::quat mRotation;

	glm::vec3 mLocalX = glm::vec3{ 1.0f, 0.0f, 0.0f };
	glm::vec3 mLocalY = glm::vec3{ 0.0f, 1.0f, 0.0f };
	glm::vec3 mLocalZ = glm::vec3{ 0.0f, 0.0f, 1.0f };

	GLFWwindow* mpWindow;

	virtual void interface() override;


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
	void rotate(const glm::quat q);
	void rotate(const glm::vec3 axis, const float deg);
	void set_scalev(const glm::vec3& nSca);
	void set_scale(const float x, const float y, const float z);
	void scalev(const glm::vec3& rhs);
	void scale(const float x, const float y, const float z);

	void lookat(const glm::vec3 target);

	inline void lookat(Transform* pTransform) {
		return lookat(pTransform->position());
	}

	void set_window(GLFWwindow* pWindow);

	glm::vec3 &position();
	glm::vec3 rotation();
	glm::vec3 scale();
	GLFWwindow* window();

	inline const glm::vec3& localx() {
		return mLocalX;
	}

	inline const glm::vec3& localy() {
		return mLocalY;
	}

	inline const glm::vec3& localz() {
		return mLocalZ;
	}

	glm::mat4 model_matrix();
	virtual void start() override;
	virtual void update() override;
};

#endif