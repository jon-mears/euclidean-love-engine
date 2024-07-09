#ifndef TRANSFORM_COMPONENT_HPP
#define TRANSFORM_COMPONENT_HPP
#include "component.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GameObject;
class GLFWwindow;

class TransformComponent : public Component {
private:
	glm::vec3 mPosition;
	glm::vec3 mEulerRotation;
	glm::vec3 mScale;

	// should be a normalized quaternion
	glm::quat mQuatRotation;

	glm::vec3 mLocalX = glm::vec3{ 1.0f, 0.0f, 0.0f };
	glm::vec3 mLocalY = glm::vec3{ 0.0f, 1.0f, 0.0f };
	glm::vec3 mLocalZ = glm::vec3{ 0.0f, 0.0f, 1.0f };

	GLFWwindow* mpWindow;

	virtual void Interface() override;


public:
	TransformComponent(GameObject* pGO);
	void SetPosition(const glm::vec3& new_position);
	void SetPosition(const float x, const float y, const float z);
	void Translate(const glm::vec3& trans);
	void Translate(const float x, const float y, const float z);
	void SetEulerRotation(const glm::vec3& euler_rotation);
	void SetEulerRotation(const float x, const float y, const float z);
	void EulerRotate(const glm::vec3& degs);
	void EulerRotate(const float x, const float y, const float z);
	void QuatRotate(const glm::quat q);
	void RotateAboutAxis(const glm::vec3& axis, const float deg);
	void SetScale(const glm::vec3& new_scale);
	void SetScale(const float x, const float y, const float z);
	void Scale(const glm::vec3& rhs);
	void Scale(const float x, const float y, const float z);

	void LookAt(const glm::vec3& target);

	inline void LookAt(TransformComponent* pTransform) {
		return LookAt(pTransform->Position());
	}

	void SetWindow(GLFWwindow* pWindow);

	const glm::vec3 &Position() const;
	const glm::vec3 &EulerRotation() const;
	const glm::vec3 &Scale() const;
	const GLFWwindow* Window() const;

	inline const glm::vec3& LocalX() {
		return mLocalX;
	}

	inline const glm::vec3& LocalY() {
		return mLocalY;
	}

	inline const glm::vec3& LocalZ() {
		return mLocalZ;
	}

	glm::mat4 ModelMatrix();
	virtual void Start() override;
	virtual void Update() override;
};

#endif