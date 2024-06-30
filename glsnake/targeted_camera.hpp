#ifndef TARGETED_CAMERA
#define TARGETED_CAMERA

#include "camera.h"
#include <glm/glm.hpp>


class TargetedCamera : public Camera {
private:
	glm::vec3 mTarget;
public:
	TargetedCamera(GameObject* gameobject);
	virtual glm::mat4 view_matrix() override;

	void set_target(const glm::vec3 target) {
		mTarget = target;
	}

	inline const glm::vec3& target() const {
		return mTarget;
	}
};

#endif