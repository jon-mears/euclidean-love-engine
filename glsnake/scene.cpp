#include "scene.hpp"
#include "app.hpp"
#include "image.hpp"
#include "texture.hpp" 
#include "transform-component.hpp"
#include "orthographic-component.hpp"
#include "game-object.hpp"
#include "camera-component.hpp"
#include "shader-component.hpp"
#include "shader.hpp"
#include "mesh.hpp"
#include "vertex-data.hpp"
#include "mesh-component.hpp"
#include "primitives.hpp"
#include "perspective-component.hpp"
#include "resource-manager.hpp"
#include "input-manager.hpp"
#include "camera-control-component.hpp"
#include "targeted-camera-component.hpp"

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


void UniformFunction(GameObject* pGO, CameraComponent* pCameraC) {
	ShaderComponent* pShaderC = pGO->Retrieve<ShaderComponent>();
	TransformComponent* pTransformC = pGO->Retrieve<TransformComponent>();
	OrthographicComponent* pOrthoC = pGO->Retrieve<OrthographicComponent>();

	glm::mat4 model = pTransformC->ModelMatrix();

	glm::mat4 proj = pOrthoC->ProjectionMatrix();

	glm::mat4 view = pCameraC->ViewMatrix();

	glm::mat4 MVP = proj * view * model;

	pShaderC->SetUniform("uMVP", MVP);
	pShaderC->UploadUniforms();
}

void InitSnake(App* pApp) {
	Shader *pBoxShader = ResourceManager::Instance().Retrieve<Shader>("Texture Shader");
	Mesh* pBoxMesh = Primitives::Cube<Vertex::POSITION | Vertex::TEXTURE_COORD>();

	Texture2D* pBoxTexture = ResourceManager::Instance().Retrieve<Texture2D>("Container");

	GameObject* pBoxObj = ResourceManager::Instance().New<GameObject>("Box");

	TransformComponent* pTransformC = pBoxObj->Add<TransformComponent>();
	pTransformC->SetScale(1.0f, 1.0f, 1.0f);
	pTransformC->SetWindow(App::Instance().Window());

	OrthographicComponent *pOrthoC = pBoxObj->Add<OrthographicComponent>();

	MeshComponent* pMeshC = pBoxObj->Add<MeshComponent>();
	pMeshC->SetMesh(pBoxMesh);

	ShaderComponent* pShaderC = pBoxObj->Add<ShaderComponent>();
	pShaderC->SetShader(pBoxShader);
	pShaderC->SetUniform("uSampler", pBoxTexture);
	pShaderC->SetUniform("uColor", glm::vec4{ 1.0f, 1.0f,
		1.0f, 1.0f });
	pShaderC->AddUpdater(UniformFunction);

	GameObject* pCameraObj = ResourceManager::Instance().New<GameObject>("Camera");

	pTransformC = pCameraObj->Add<TransformComponent>();
	pTransformC->SetPosition(0.0f, 0.0f, 0.5f);
	pTransformC->SetWindow(App::Instance().Window());

	TargetedCameraComponent* pCameraC = pCameraObj->Add<TargetedCameraComponent>();

	pShaderC = pBoxObj->Retrieve<ShaderComponent>();

	CameraControlComponent* pCameraControl = pCameraObj->Add<CameraControlComponent>();
	pCameraControl->ToggleActive();
	pCameraControl->ToggleActive();

	pCameraC->AddViewable(pBoxObj);

	// translation gizmo

	Mesh* pXVec = Primitives::Line<1, 0, 0>();
	Mesh* pYVec = Primitives::Line<0, 1, 0>();
	Mesh* pZVec = Primitives::Line<0, 0, 1>();

	GameObject* pTranslationGizmo = ResourceManager::Instance().New<GameObject>("Translation Gizmo");
	pMeshC = pTranslationGizmo->Add<MeshComponent>();
	pMeshC->SetMesh(pXVec);
	pMeshC->SetRenderMode(GL_LINES);
}

void DeinitSnake(App* pApp) {

}