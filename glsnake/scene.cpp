#include "scene.hpp"
#include "space.hpp"
#include "app.hpp"
#include "color.hpp"
#include "image.hpp"
#include "texture.hpp" 
#include "transform-component.hpp"
#include "game-object.hpp"
#include "camera-component.hpp"
#include "shader.hpp"
#include "mesh.hpp"
#include "vertex-data.hpp"
#include "material.hpp"
#include "primitives.hpp"
#include "editor-manager.hpp"
#include "resource-manager.hpp"
#include "input-manager.hpp"
#include "render-component.hpp"
#include "projection.hpp"
#include "free-camera-component.hpp"
#include "test-component.hpp"
#include "transform-gizmo.hpp"

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

	// retrieve editor manager
	EditorManager& em = EditorManager::Instance();

	// setup camera
	auto pCameraObj = rm.New<GameObject>("Camera");
	auto pFreeCameraC = pCameraObj->Add<FreeCameraComponent>();

	auto pTransformC = pCameraObj->Add<TransformComponent>();
	pTransformC->SetPosition(glm::vec3{ 0.0f, 0.0f, 8.0f });
	pTransformC->SetEulerRotation(Rad(0.0f), Rad(0.0f), Rad(0.0f));

	pCameraObj->Add<TestComponent>();

	// save camera info to editor manager
	em.SetEditorCamera(pFreeCameraC);

	// setup box object
	auto pBoxObj = rm.New<GameObject>("Box1");
	auto pBoxObj2 = rm.New<GameObject>("Box2");

	// shader/material
	auto pBoxShader = rm.Retrieve<Shader>("Texture Shader");
	auto pBoxTexture = rm.Retrieve<Texture2D>("Container");
	auto pBoxMaterial = new Material(pBoxShader);
	auto pBoxMaterial2 = new Material(pBoxShader);
	pBoxMaterial->SetUniform("uSampler", pBoxTexture);
	pBoxMaterial->SetUniform("uColor", glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f });

	pBoxMaterial2->SetUniform("uSampler", pBoxTexture);
	pBoxMaterial2->SetUniform("uColor", glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f });

	// mesh
	auto pBoxMesh =
		Primitives::Cube<Vertex::POSITION | Vertex::TEXTURE_COORD>();

	// transform
	auto pBoxTransformC = pBoxObj->Add<TransformComponent>();
	pBoxTransformC->SetPosition(glm::vec3{ -2.0f, 0.0f, 0.0f });
	pBoxTransformC->SetScale(
		glm::vec3{ 1.0f, 1.0f, 1.0f }
	);

	auto pBoxTransformC2 = pBoxObj2->Add<TransformComponent>();
	pBoxTransformC2->SetPosition(glm::vec3{ 2.0f, 0.0f, 0.0f });
	pBoxTransformC2->SetScale(
		glm::vec3{ 1.0f, 1.0f, 1.0f }
	);

	// render
	RenderComponent* pRenderC = pBoxObj->Add<RenderComponent>();
	pRenderC->SetMaterial(pBoxMaterial);
	pRenderC->SetMesh(pBoxMesh);
	pRenderC->SetCamera(pFreeCameraC);
	pRenderC->SetProjection(new Perspective());

	pBoxObj->Add<TransformGizmo>();

	pRenderC = pBoxObj2->Add<RenderComponent>();
	pRenderC->SetMaterial(pBoxMaterial2);
	pRenderC->SetMesh(pBoxMesh);
	pRenderC->SetCamera(pFreeCameraC);
	pRenderC->SetProjection(new Perspective());

	pBoxObj2->Add<TransformGizmo>();

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
	pStingTransformC->SetPosition(glm::vec3{ 0.0f, 2.0f, 0.0f });
	pStingTransformC->SetScale(
		glm::vec3{ 1.0f, 1.0f, 1.0f }
	);
	
	pBoxTransformC->AddChild(pStingTransformC);
	pStingTransformC->AddChild(pBoxTransformC2);

	// render
	pRenderC = pStingrayObj->Add<RenderComponent>();
	pRenderC->SetMaterial(pStingrayMaterial);
	pRenderC->SetMesh(pStingrayMesh);
	pRenderC->SetCamera(pFreeCameraC);
	pRenderC->SetProjection(new Perspective());

	pStingrayObj->Add<TransformGizmo>();

	//new Line<
	//	0, 0, 0,
	//	1, 0, 0
	//	>(pFreeCameraC, Color::RED);

	//new Line<
	//	0, 0, 0,
	//	0, 1, 0
	//>(pFreeCameraC, Color::GREEN);

	//new Line<
	//	0, 0, 0,
	//	0, 0, 1
	//>(pFreeCameraC, Color::BLUE);

	//rm.Add<GameObject>(
	//	new Line<0, 0, 0, 1, 0, 0>(pFreeCameraC, Color::RED),
	//	"X Axis"
	//);

	//rm.Add<GameObject>(
	//	new Line<0, 0, 0, 0, 1, 0>(pFreeCameraC, Color::GREEN),
	//	"Y Axis"
	//);

	//rm.Add<GameObject>(
	//	new Line<0, 0, 0, 0, 0, 1>(pFreeCameraC, Color::BLUE),
	//	"Z Axis"
	//);

	// would be cool to allow the user to specify the size of the UI
	// element using a UDL percentage (of the current window width/height) or using 
	// GLFW (or windowing system) units

	glm::vec3 x1, y1, z1, o1, x2, y2, z2, o2;

	x1 = glm::vec3{ 1,0,0 };
	y1 = glm::vec3{ 0,1,0 };
	z1 = glm::vec3{ 0,0,1 };
	o1 = glm::vec3{ 0,0,0 };

	x2 = glm::vec3{ 0,0,-1 };
	y2 = glm::vec3{ 0,1,0 };
	z2 = glm::vec3{ 1,0,0 };
	o2 = glm::vec3{ 1,0,1 };

	Space* pSpace1 = new Space(x1, y1, z1, o1);
	Space* pSpace2 = new Space(x2, y2, z2, o2);

	glm::vec3 point{ 5,3,2 };

	glm::vec3 intermed = pSpace1->Space2World(point);
	glm::vec3 result = pSpace2->World2Space(intermed);
}

void DeinitSnake(App* pApp) {

}