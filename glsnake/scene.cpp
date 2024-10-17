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

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
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

	GameObject* pBoxObj2 = ResourceManager::Instance().New<GameObject>("Box2");

	TransformComponent* pTransformC = pBoxObj->Add<TransformComponent>();
	pTransformC->SetScale(1.0f, 1.0f, 1.0f);
	pTransformC->SetWindow(App::Instance().Window());

	pTransformC = pBoxObj2->Add<TransformComponent>();
	pTransformC->SetPosition(0.5f, 0.0f, 0.0f);

	GameObject* pCameraObj = ResourceManager::Instance().New<GameObject>("Camera");
		
	pTransformC = pCameraObj->Add<TransformComponent>();
	pTransformC->SetPosition(0.0f, 0.0f, 0.5f);
	pTransformC->SetWindow(App::Instance().Window());

	TargetedCameraComponent* pCameraC = pCameraObj->Add<TargetedCameraComponent>();

	CameraControlComponent* pCameraControl = pCameraObj->Add<CameraControlComponent>();

	// secretly adds gameobject to engine dstructure to render objects in order
	RenderComponent* pRenderC = pBoxObj->Add<RenderComponent>();
	Material* pBoxMaterial = new Material(pBoxShader);
	pRenderC->SetMaterial(pBoxMaterial);
	pRenderC->SetMesh(pBoxMesh);
	pRenderC->SetCamera(pCameraC);
	pRenderC->SetProjection(new Orthographic());
	//pRenderC->SetLayer(0);
	pBoxMaterial->SetUniform("uColor", glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f });
	pBoxMaterial->SetUniform("uSampler", pBoxTexture);

	pRenderC = pBoxObj2->Add<RenderComponent>();
	Material* pBoxMaterial2 = new Material(pBoxShader);
	pRenderC->SetMaterial(pBoxMaterial2);
	pRenderC->SetMesh(pBoxMesh);
	pRenderC->SetCamera(pCameraC);
	pRenderC->SetProjection(new Orthographic());
	//pRenderC->SetLayer(0);
	pBoxMaterial2->SetUniform("uColor", glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });
	pBoxMaterial2->SetUniform("uSampler", pBoxTexture);
}

void DeinitSnake(App* pApp) {

}