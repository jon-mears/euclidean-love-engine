#ifndef PROJECTION_COMPONENT_HPP
#define PROJECTION_COMPONENT_HPP

#include "component.hpp"

#include <glm/glm.hpp>

class GameObject;

class ProjectionComponent : public Component {
public:
	ProjectionComponent(GameObject* pGO);
	virtual glm::mat4 ProjectionMatrix() = 0;

	virtual void Start() override;
	virtual void Update() override;
	virtual void ConstUpdate() const override;
};
#endif