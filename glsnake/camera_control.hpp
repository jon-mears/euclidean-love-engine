#ifndef CAMERA_CONTROL_HPP
#define CAMERA_CONTROL_HPP
#include "component.h"

#include <glm/glm.hpp>

class GameObject;
class Transform;
class TargetedCamera;

class CameraControl : public Component {
private:
	Transform* mpTransform;
	TargetedCamera* mpTargetedCamera;

	struct {
		glm::vec3 position;
		float distance;
		float longitude;
		float latitude;
	} mOrbitTarget;

	struct {
		float longitude;
		float latitude;
	} mLookTarget;

public:
	CameraControl(GameObject* gameobject);
	virtual void start() override;
	virtual void update() override;

	float mXPanSpeed = 0.01f;
	float mYPanSpeed = 0.01f;
	float mXOrbitSpeed = 0.1f;
	float mYOrbitSpeed = 0.1f;
	float mXLookSpeed = 0.01f;
	float mYLookSpeed = 0.01f;
};
#endif