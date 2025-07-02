#include "camera-component.hpp"
#include "shader-component.hpp"
#include "mesh-component.hpp"
#include "transform-component.hpp"
#include "game-object.hpp"
#include "component.hpp"
#include "framebuffer.hpp"
#include "vertex-data.hpp"
#include "mesh.hpp"
#include "render-engine.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/euler_angles.hpp>

CameraComponent::CameraComponent(GameObject* pGO) : Component(pGO), mViewables(), mpTransform(nullptr) { }

void CameraComponent::Start() {
	mpTransform = GetComponent<TransformComponent>();
	RenderEngine::Instance().AddCamera(this);
}

void CameraComponent::Update() { }

void CameraComponent::ConstUpdate() const { }

void CameraComponent::AddViewable(GameObject* pGO) {
	if (std::find(mViewables.begin(), mViewables.end(), pGO)
		== mViewables.end()) {
		mViewables.push_back(pGO);
	}
}

//void CameraComponent::Draw() {
//	//glViewport(mOriginX, mOriginY, mWidth, mHeight);
//
//	if (mpFramebuffer == nullptr) {
//		glBindFramebuffer(GL_FRAMEBUFFER, 0);
//	}
//
//	else {
//		mpFramebuffer->Enable();
//	}
//
//	for (GameObject* pViewable : mViewables) {
//
//		// if it's not owned, might be a good idea to return a 
//		// const-reference
//
//		ShaderComponent* pShaderComponent = pViewable->Retrieve<ShaderComponent>();
//		MeshComponent* pMeshComponent = pViewable->Retrieve<MeshComponent>();
//
//		if ((pShaderComponent == nullptr || !pShaderComponent->IsActive()) ||
//			(pMeshComponent == nullptr || !pMeshComponent->IsActive())) {
//			// do nothing
//		}
//
//		else {
//			pShaderComponent->UpdateUniforms(this);
//			pShaderComponent->UploadUniforms();
//
//			pShaderComponent->Enable();
//			pMeshComponent->Enable();
//
//			glDrawArrays(pMeshComponent->GetRenderMode(), 0, pMeshComponent->NumVertices());
//		}
//	}
//}

glm::mat4 CameraComponent::ViewMatrix() {
	glm::vec3 pos = mpTransform->Position();
	//glm::vec3 rot = mpTransform->EulerRotation();

	//glm::mat4 rotation_matrix{ 1 };

	//glm::mat4 rotation_matrix = glm::yawPitchRoll(rot.y, rot.x, rot.z);

	//rotation_matrix = glm::rotate(rotation_matrix, rot.x, glm::vec3(1, 0, 0));
	//rotation_matrix = glm::rotate(rotation_matrix, rot.y, glm::vec3(0, 1, 0));
	//rotation_matrix = glm::rotate(rotation_matrix, rot.z, glm::vec3(0, 0, 1));

	//glm::vec4 center4 = rotation_matrix * glm::vec4{ 0, 0, -1, 0 };

	//glm::vec3 center3{};
	//center3.x = center4.x;
	//center3.y = center4.y;
	//center3.z = center4.z;

	//return glm::lookAt(pos, pos - mpTransform->LocalZ(), glm::vec3{0.0f, 1.0f, 0.0f});

	glm::vec3 x = mpTransform->LocalX();
	glm::vec3 y = mpTransform->LocalY();
	glm::vec3 z = mpTransform->LocalZ();

	glm::mat4 rotation_matrix(
		x.x, y.x, z.x, 0,
		x.y, y.y, z.y, 0,
		x.z, y.z, z.z, 0,
		0, 0, 0, 1
	);

	glm::mat4 translation_matrix(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-pos.x, -pos.y, -pos.z, 1
	);

	return rotation_matrix * translation_matrix;
}