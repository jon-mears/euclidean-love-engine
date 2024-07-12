#include "camera-component.hpp"
#include "shader-component.hpp"
#include "mesh-component.hpp"
#include "transform-component.hpp"
#include "game-object.hpp"
#include "component.hpp"
#include "framebuffer.hpp"
#include "vertex-data.hpp"
#include "mesh.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

CameraComponent::CameraComponent(GameObject* pGO) : Component(pGO), mViewables(), mpTransform(nullptr) { }

void CameraComponent::Start() { 
	mpTransform = GetComponent<TransformComponent>();
}

void CameraComponent::Update() { }

void CameraComponent::ConstUpdate() const { }

void CameraComponent::AddViewable(GameObject* pGO) {
	if (std::find(mViewables.begin(), mViewables.end(), pGO)
		== mViewables.end()) {
		mViewables.push_back(pGO);
	}	
}

void CameraComponent::Draw() {
	//glViewport(mOriginX, mOriginY, mWidth, mHeight);

	if (mpFramebuffer == nullptr) {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	else {
		mpFramebuffer->Enable();
	}

	for (GameObject* pViewable : mViewables) {

		// if it's not owned, might be a good idea to return a 
		// const-reference

		ShaderComponent* pShaderComponent = pViewable->Retrieve<ShaderComponent>();
		MeshComponent* pMeshComponent = pViewable->Retrieve<MeshComponent>();

		if (pShaderComponent == nullptr) {
			std::cerr << "NEED A SHADERCOMPONENT TO RENDER!!!" << std::endl;
			std::exit(-1);
		}
		if (pMeshComponent == nullptr) {
			std::cerr << "NEED A MESHCOMPONENT TO RENDER!!!" << std::endl;
			std::exit(-1);
		}

		pShaderComponent->UpdateUniforms(this);
		pShaderComponent->UploadUniforms();

		pShaderComponent->Enable();
		pMeshComponent->Enable();

		glDrawArrays(pMeshComponent->GetRenderMode(), 0, pMeshComponent->NumVertices());
	}
}

glm::mat4 CameraComponent::ViewMatrix() {
	glm::vec3 pos = mpTransform->Position();
	glm::vec3 rot = mpTransform->EulerRotation();

	glm::mat4 rotation_matrix{ 1 };

	rotation_matrix = glm::rotate(rotation_matrix, rot.x, glm::vec3(1, 0, 0));
	rotation_matrix = glm::rotate(rotation_matrix, rot.y, glm::vec3(0, 1, 0));
	rotation_matrix = glm::rotate(rotation_matrix, rot.z, glm::vec3(0, 0, 1));


	glm::vec4 center4 = rotation_matrix * glm::vec4{ 0, 0, -1, 0 };

	glm::vec3 center3{};
	center3.x = center4.x;
	center3.y = center4.y;
	center3.z = center4.z;

	return glm::lookAt(pos, pos + center3, glm::vec3{ 0.0f, 1.0f, 0.0f });
}