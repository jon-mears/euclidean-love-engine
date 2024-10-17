#ifndef TARGETED_CAMERA_COMPONENT_HPP
#define TARGETED_CAMERA_COMPONENT_HPP

#include "camera-component.hpp"
#include <glm/glm.hpp>


class TargetedCameraComponent : public CameraComponent {
private:
	glm::vec3 mTarget;
public:
	TargetedCameraComponent(GameObject* pGO);
	virtual glm::mat4 ViewMatrix() override;

	void SetTarget(const glm::vec3 target) {
		mTarget = target;
	}

	inline const glm::vec3& Target() const {
		return mTarget;
	}
};

#endif