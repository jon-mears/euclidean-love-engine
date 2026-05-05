#include "camera-component.hpp"

#include <algorithm>

#include <glm/glm.hpp>

#include "component.hpp"
#include "render-engine.hpp"
#include "transform-component.hpp"

class Framebuffer;
class GameObject;

CameraComponent::CameraComponent(GameObject* GO) :
	Component{ GO }, mpTransform{ nullptr }, mpFramebuffer{ nullptr },
	mViewables{ }
{ }

void CameraComponent::Start() {
	auto& re{ RenderEngine::Instance() };

	mpTransform = Get<TransformComponent>();

	re.AddCamera(this);
}

void CameraComponent::Update() { }

void CameraComponent::ConstUpdate() const { }

char const* CameraComponent::Name() const {
	return "Camera";
}

void CameraComponent::AddViewable(GameObject* GO) {
	mViewables.insert(GO);
}

::Framebuffer* CameraComponent::Framebuffer() {
	return mpFramebuffer;
}

void CameraComponent::SetFramebuffer(::Framebuffer* framebuffer) {
	mpFramebuffer = framebuffer;
}

glm::mat4 CameraComponent::ViewMatrix() {
	glm::vec3 pos{ mpTransform->Position() };

	glm::vec3 x{ mpTransform->X() };
	glm::vec3 y{ mpTransform->Y() };
	glm::vec3 z{ mpTransform->Z() };

	glm::mat4 rotation_matrix{
		x.x, y.x, z.x, 0,
		x.y, y.y, z.y, 0,
		x.z, y.z, z.z, 0,
		0, 0, 0, 1
	};

	glm::mat4 translation_matrix{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-pos.x, -pos.y, -pos.z, 1
	};

	return rotation_matrix * translation_matrix;
}