#ifndef PERSPECTIVE_COMPONENT_HPP
#define PERSPECTIVE_COMPONENT_HPP

#include <glm/glm.hpp>
#include "projection-component.hpp"

class GameObject;

class PerspectiveComponent : public ProjectionComponent {
private:
	float mFOVY, mAspect, mNear, mFar;

public:
	PerspectiveComponent(GameObject* pGO);
	virtual glm::mat4 ProjectionMatrix() override;
};
#endif