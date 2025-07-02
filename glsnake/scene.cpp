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
#include "material.hpp"
#include "mesh-component.hpp"
#include "primitives.hpp"
#include "perspective-component.hpp"
#include "resource-manager.hpp"
#include "input-manager.hpp"
#include "camera-control-component.hpp"
#include "targeted-camera-component.hpp"
#include "render-component.hpp"
#include "projection.hpp"
#include "free-camera-component.hpp"

#include "ui-rectangle.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

//void UniformFunction(GameObject* pGO, CameraComponent* pCameraC) {
//	ShaderComponent* pShaderC = pGO->Retrieve<ShaderComponent>();
//	TransformComponent* pTransformC = pGO->Retrieve<TransformComponent>();
//	OrthographicComponent* pOrthoC = pGO->Retrieve<OrthographicComponent>();
//
//	glm::mat4 model = pTransformC->ModelMatrix();
//
//	glm::mat4 proj = pOrthoC->ProjectionMatrix();
//
//	glm::mat4 view = pCameraC->ViewMatrix();
//
//	glm::mat4 MVP = proj * view * model;
//
//	pShaderC->SetUniform("uMVP", MVP);
//	pShaderC->UploadUniforms();
//}

void InitSnake(App* pApp) {
	Shader *pBoxShader = ResourceManager::Instance().Retrieve<Shader>("Color Shader");
	Mesh* pBoxMesh = ResourceManager::Instance().Retrieve<Mesh>("Stingray");

	pBoxMesh = Primitives::Plane<Vertex::POSITION>();

	Texture2D* pBoxTexture = ResourceManager::Instance().Retrieve<Texture2D>("Container");

	GameObject* pBoxObj = ResourceManager::Instance().New<GameObject>("Box");

	GameObject* pBoxObj2 = ResourceManager::Instance().New<GameObject>("Box2");

	TransformComponent* pTransformC = pBoxObj->Add<TransformComponent>();
	pTransformC->SetScale(glm::vec3{ 1.0f / 30.0f, 1.0f / 30.0f, 1.0f / 30.0f });

	pTransformC = pBoxObj2->Add<TransformComponent>();
	pTransformC->SetPosition(glm::vec3{ 0.5f, 0.0f, 0.0f });

	GameObject* pCameraObj = ResourceManager::Instance().New<GameObject>("Camera");
		
	pTransformC = pCameraObj->Add<TransformComponent>();
	pTransformC->SetPosition(glm::vec3{ 0.0f, 0.0f, 0.5f });
	pTransformC->SetEulerRotation(glm::vec3{ 0, 0, 0 });

	auto pCameraC = pCameraObj->Add<FreeCameraComponent>();

	// secretly adds gameobject to engine dstructure to render objects in order
	RenderComponent* pRenderC = pBoxObj->Add<RenderComponent>();
	Material* pBoxMaterial = new Material(pBoxShader);
	pRenderC->SetMaterial(pBoxMaterial);
	pRenderC->SetMesh(pBoxMesh);
	pRenderC->SetCamera(pCameraC);
	pRenderC->SetProjection(new Perspective());
	pBoxMaterial->SetUniform("uColor", glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f });

	new UIRectangle(0.5, 0.5, ResourceManager::Instance().Retrieve<Texture2D>("Container"));
}

void DeinitSnake(App* pApp) {

}	