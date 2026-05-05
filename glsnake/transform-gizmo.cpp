#include "transform-gizmo.hpp"

#include <memory>
#include <iostream>

#include "editor-manager.hpp"
#include "line.hpp"
#include "space.hpp"

class CameraComponent;

TransformGizmo::TransformGizmo(GameObject* GO) :
	Component{ GO }, muX{ }, muY{ }, muZ{ }, muO{ }, mpTransformC{
	nullptr},
	mpTransformX{ nullptr }, mpTransformY{ nullptr }, mpTransformZ{ nullptr },
	mpTransformO{ nullptr }
{ }

void TransformGizmo::Start() {
	auto& em{ EditorManager::Instance() };

	auto camera{ em.EditorCamera() };

	muX = std::make_unique<Line<0, 0, 0, 1, 0, 0>>(camera, Color::RED);
	muY = std::make_unique<Line<0, 0, 0, 0, 1, 0>>(camera, Color::GREEN);
	muZ = std::make_unique<Line<0, 0, 0, 0, 0, 1>>(camera, Color::BLUE);
	muO = std::make_unique<Point>(camera, Color::WHITE);

	mpTransformC = mpGO->Retrieve<TransformComponent>();

	mpTransformX = muX->Retrieve<TransformComponent>();
	mpTransformY = muY->Retrieve<TransformComponent>();
	mpTransformZ = muZ->Retrieve<TransformComponent>();
	mpTransformO = muO->Retrieve<TransformComponent>();

	muX->Start();
	muY->Start();
	muZ->Start();
	muO->Start();
}

void TransformGizmo::Update() {

	//std::cout << glm::to_string(mpTransformC->Position(Space::OBJECT)) << std::endl;
	mpTransformX->SetPosition(mpTransformC->Position(Space::WORLD));

	glm::vec3 euler{ mpTransformC->EulerRotation(Space::LOCAL) };

	mpTransformX->SetEulerRotation(
		Rad(euler.x), Rad(euler.y), Rad(euler.z)
	);

	mpTransformY->SetPosition(mpTransformC->Position(Space::WORLD));

	mpTransformY->SetEulerRotation(
		Rad(euler.x), Rad(euler.y), Rad(euler.z)
	);

	mpTransformZ->SetPosition(mpTransformC->Position(Space::WORLD));

	mpTransformZ->SetEulerRotation(
		Rad(euler.x), Rad(euler.y), Rad(euler.z)
	);

	mpTransformO->SetPosition(mpTransformC->Position(Space::WORLD));

	muX->Update();
	muY->Update();
	muZ->Update();
	muO->Update();
}

void TransformGizmo::ConstUpdate() const { }

char const* TransformGizmo::Name() const {
	return "Transform Gizmo";
}