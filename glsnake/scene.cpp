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

void InitSnake(App* pApp) {
	// retrieve resource manager
	ResourceManager& rm = ResourceManager::Instance();

	// setup camera
	auto pCameraObj = rm.New<GameObject>("Camera");
	auto pFreeCameraC = pCameraObj->Add<FreeCameraComponent>();

	auto pTransformC = pCameraObj->Add<TransformComponent>();
	pTransformC->SetPosition(glm::vec3{ 0.0f, 0.0f, 0.5f });
	pTransformC->SetEulerRotation(glm::vec3{ 0, 0, 0 });

	// setup box object
	auto pBoxObj = rm.New<GameObject>("Box");

	// shader/material
	auto pBoxShader = rm.Retrieve<Shader>("Texture Shader");
	auto pBoxTexture = rm.Retrieve<Texture2D>("Container");
	auto pBoxMaterial = new Material(pBoxShader);
	pBoxMaterial->SetUniform("uSampler", pBoxTexture);
	pBoxMaterial->SetUniform("uColor", glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f });

	// mesh
	auto pBoxMesh =
		Primitives::Cube<Vertex::POSITION | Vertex::TEXTURE_COORD>();

	// transform
	auto pBoxTransformC = pBoxObj->Add<TransformComponent>();
	pBoxTransformC->SetPosition(glm::vec3{ -0.1f, 0.0f, 0.0f });
	pBoxTransformC->SetScale(
		glm::vec3{ 1.0f / 30.0f, 1.0f / 30.0f, 1.0f / 30.0f }
	);

	// render
	RenderComponent* pRenderC = pBoxObj->Add<RenderComponent>();
	pRenderC->SetMaterial(pBoxMaterial);
	pRenderC->SetMesh(pBoxMesh);
	pRenderC->SetCamera(pFreeCameraC);
	pRenderC->SetProjection(new Perspective());

	// setup stingray object
	auto pStingrayObj = rm.New<GameObject>("Stingray");
	
	// shader/material
	auto pStingrayShader = rm.Retrieve<Shader>("Color Shader");
	auto pStingrayMaterial = new Material(pStingrayShader);
	pStingrayMaterial->SetUniform("uColor",
		glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f });

	// mesh
	auto pStingrayMesh = rm.Retrieve<Mesh>("Stingray");

	// transform
	auto pStingTransformC = pStingrayObj->Add<TransformComponent>();
	pStingTransformC->SetPosition(glm::vec3{ 0.1, 0.0f, 0.0f });
	pStingTransformC->SetScale(
		glm::vec3{ 1.0f / 30.0f, 1.0f / 30.0f, 1.0f / 30.0f }
	);
	pStingTransformC->SetParent(pBoxTransformC);

	// render
	pRenderC = pStingrayObj->Add<RenderComponent>();
	pRenderC->SetMaterial(pStingrayMaterial);
	pRenderC->SetMesh(pStingrayMesh);
	pRenderC->SetCamera(pFreeCameraC);
	pRenderC->SetProjection(new Perspective());

	// would be cool to allow the user to specify the size of the UI
	// element using a UDL percentage (of the current window width/height) or using 
	// GLFW (or windowing system) units
	//new UIRectangle(0.5, 0.5, rm.Retrieve<Texture2D>("Container"));
}

void DeinitSnake(App* pApp) {

}