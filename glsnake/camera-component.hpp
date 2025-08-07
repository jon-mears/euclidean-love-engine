#ifndef CAMERA_COMPONENT_HPP
#define CAMERA_COMPONENT_HPP

#include <unordered_set>

#include <glm/glm.hpp>

#include "component.hpp"

class TransformComponent;
class GameObject;
class Framebuffer;

class CameraComponent : public Component {
public:
	CameraComponent(GameObject* GO);

	virtual void Start() override;
	virtual void Update() override;
	virtual void ConstUpdate() const override;

	virtual char const* Name() const override;

	void AddViewable(GameObject* GO);

	::Framebuffer* Framebuffer();

	void SetFramebuffer(::Framebuffer* framebuffer);

	virtual glm::mat4 ViewMatrix();

protected:
	TransformComponent* mpTransform;
	::Framebuffer* mpFramebuffer;

private:
	std::unordered_set<GameObject*> mViewables;
};
#endif