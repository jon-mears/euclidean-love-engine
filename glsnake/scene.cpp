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

const Scene Init_Scene = static_cast<Scene>(0);

void UniformUpdater(GameObject* pGO, CameraComponent* pCameraC) {
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
	Shader *pBoxShader = ResourceManager::Instance().Retrieve<Shader>("Texture");

	Mesh* pBoxMesh = Primitives::Cube(Vertex::POSITION | Vertex::TEXTURE_COORD);

	Image2D* pBoxImage = new Image2D();
	pBoxImage->Open("C:\\assets\\container.jpg");
	Texture2D* pBoxTexture = new Texture2D();

	pBoxTexture->SetImage(pBoxImage);

	GameObject* pBoxObj = ResourceManager::Instance().New<GameObject>("Box");

	TransformComponent* pTransformC = pBoxObj->Add<TransformComponent>();
	pTransformC->SetScale(0.25f, 0.25f, 0.25f);
	pTransformC->SetWindow(App::Instance().Window());

	OrthographicComponent *pOrthoC = pBoxObj->Add<OrthographicComponent>();

	MeshComponent* pMeshC = pBoxObj->Add<MeshComponent>();
	pMeshC->SetMesh(pBoxMesh);

	ShaderComponent* pShaderC = pBoxObj->Add<ShaderComponent>();
	pShaderC->SetShader(pBoxShader);
	pShaderC->SetUniform("uSampler", pBoxTexture);
	pShaderC->AddUpdater(UniformUpdater);

	GameObject* pCameraObj = ResourceManager::Instance().New<GameObject>("Camera");

	pTransformC = pCameraObj->Add<TransformComponent>();
	pTransformC->SetWindow(App::Instance().Window());

	CameraComponent* pCameraC = pCameraObj->Add<TargetedCameraComponent>();
	pCameraObj->Add<CameraControlComponent>();
	pCameraC->AddViewable(pBoxObj);
}

void DeinitSnake(App* pApp) {

}