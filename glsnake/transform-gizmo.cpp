#include <iostream>

#include "camera-component.hpp"
#include "editor-manager.hpp"
#include "transform-gizmo.hpp"

#include "line.hpp"

void TransformGizmo::Start() {
	EditorManager& em = EditorManager::Instance();

	CameraComponent* pCameraC = em.EditorCamera();

	mX = new Line<0, 0, 0, 1, 0, 0>(pCameraC, Color::RED);
	mY = new Line<0, 0, 0, 0, 1, 0>(pCameraC, Color::GREEN);
	mZ = new Line<0, 0, 0, 0, 0, 1>(pCameraC, Color::BLUE);

	mpTransformC = mpGO->Retrieve<TransformComponent>();

	mpTransformX = mX->Retrieve<TransformComponent>();
	mpTransformY = mY->Retrieve<TransformComponent>();
	mpTransformZ = mZ->Retrieve<TransformComponent>();

	mX->Start();
	mY->Start();
	mZ->Start();
}

void TransformGizmo::Update() {
	mpTransformX->SetPosition(mpTransformC->Position());
	mpTransformX->SetEulerRotation(mpTransformC->EulerRotation());

	mpTransformY->SetPosition(mpTransformC->Position());
	mpTransformY->SetEulerRotation(mpTransformC->EulerRotation());

	mpTransformZ->SetPosition(mpTransformC->Position());
	mpTransformZ->SetEulerRotation(mpTransformC->EulerRotation());

	mX->Update();
	mY->Update();
	mZ->Update();
}

void TransformGizmo::ConstUpdate() const { }

const char* TransformGizmo::Name() const {
	return "Transform Gizmo";
}

TransformGizmo::TransformGizmo(GameObject* pGO) : Component(pGO) { 
}