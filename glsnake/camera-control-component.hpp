#ifndef CAMERA_CONTROL_COMPONENT_HPP
#define CAMERA_CONTROL_COMPONENT_HPP
#include "component.hpp"

#include <glm/glm.hpp>

class GameObject;
class TransformComponent;
class TargetedCameraComponent;

class CameraControlComponent : public Component {
private:
	TransformComponent* mpTransform;
	TargetedCameraComponent* mpTargetedCamera;

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
	CameraControlComponent(GameObject* pGO);
	virtual void Start() override;
	virtual void Update() override;
	virtual void ConstUpdate() const override;

	float mXPanSpeed = 0.01f;
	float mYPanSpeed = 0.01f;
	float mXOrbitSpeed = 0.1f;
	float mYOrbitSpeed = 0.1f;
	float mXLookSpeed = 0.01f;
	float mYLookSpeed = 0.01f;
};
#endif