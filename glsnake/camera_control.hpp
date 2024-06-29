#ifndef CAMERA_CONTROL_HPP
#define CAMERA_CONTROL_HPP
#include "component.h"

class GameObject;
class Transform;

class CameraControl : public Component {
private:
	Transform* mpTransform;
public:
	CameraControl(GameObject* gameobject);
	virtual void start();
	virtual void update();
};
#endif