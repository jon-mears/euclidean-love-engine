#ifndef ORTHOGRAPHIC_COMPONENT_HPP
#define ORTHOGRAPHIC_COMPONENT_HPP

#include <glm/glm.hpp>

#include "projection-component.hpp"

class GameObject;

class OrthographicComponent : public ProjectionComponent {
public:
	float mLeft, mRight, mTop, mBottom;
public:

	OrthographicComponent(GameObject* pGO);
	virtual glm::mat4 ProjectionMatrix() override;
};
#endif