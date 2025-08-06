#include "transform-gizmo.hpp"

#include <memory>

#include "editor-manager.hpp"
#include "line.hpp"

class CameraComponent;

TransformGizmo::TransformGizmo(GameObject* GO)
	: Component{ GO }, muX{ }, muY{ }, muZ{ }, mpTransformC{ nullptr },
	mpTransformX{ nullptr }, mpTransformY{ nullptr }, mpTransformZ{ nullptr }
{ }

void TransformGizmo::Start() {
	auto& em{ EditorManager::Instance() };

	auto camera{ em.EditorCamera() };

	muX = std::make_unique<Line<0, 0, 0, 1, 0, 0>>(camera, Color::RED);
	muY = std::make_unique<Line<0, 0, 0, 0, 1, 0>>(camera, Color::GREEN);
	muZ = std::make_unique<Line<0, 0, 0, 0, 0, 1>>(camera, Color::BLUE);

	mpTransformC = mpGO->Retrieve<TransformComponent>();

	mpTransformX = muX->Retrieve<TransformComponent>();
	mpTransformY = muY->Retrieve<TransformComponent>();
	mpTransformZ = muZ->Retrieve<TransformComponent>();

	muX->Start();
	muY->Start();
	muZ->Start();
}

void TransformGizmo::Update() {
	mpTransformX->SetPosition(mpTransformC->Position());
	mpTransformX->SetEulerRotation(mpTransformC->EulerRotation());

	mpTransformY->SetPosition(mpTransformC->Position());
	mpTransformY->SetEulerRotation(mpTransformC->EulerRotation());

	mpTransformZ->SetPosition(mpTransformC->Position());
	mpTransformZ->SetEulerRotation(mpTransformC->EulerRotation());

	muX->Update();
	muY->Update();
	muZ->Update();
}

void TransformGizmo::ConstUpdate() const { }

char const* TransformGizmo::Name() const {
	return "Transform Gizmo";
}