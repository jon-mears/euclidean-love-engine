#include "camera-tag.hpp"

#include <iostream>

#include "ui-rectangle.hpp"

#include "material.hpp"
#include "primitives.hpp"

#include "resource-manager.hpp"
#include "render-component.hpp"
#include "render-mode.hpp"
#include "render-engine.hpp"

#include "transform-component.hpp"
#include "game-object.hpp"

UIRectangle::UIRectangle(float width, float height, Color color, CameraTag eCameraTag) : mWidth{ width }, mHeight{ height }, mAppearance{ color } {
	mpGameObject = ResourceManager::Instance().New<GameObject>("UI Rectangle");
	auto pTransformC = mpGameObject->Add<TransformComponent>();

	pTransformC->SetScale(glm::vec3{ width, height, 1.0f });
	
	auto pRenderC = mpGameObject->Add<RenderComponent>();
	pRenderC->SetRenderMode(RenderMode::UI);

	if (eCameraTag == CameraTag::ALL) {
		std::cout << "here" << std::endl;
		for (auto it = RenderEngine::Instance().CameraBegin();
			it != RenderEngine::Instance().CameraEnd(); ++it) {
			pRenderC->SetCamera(*it);
		}
	}

	auto pShader = ResourceManager::Instance().Retrieve<Shader>("Color Shader");
	auto mat = new Material(pShader);

	mat->SetUniform("uColor", color.value);

	pRenderC->SetMaterial(mat);
	pRenderC->SetMesh(Primitives::Plane<Vertex::POSITION>());
}

UIRectangle::UIRectangle(float width, float height, Texture2D* pTexture,
	CameraTag eCameraTag) : mWidth{ width }, mHeight{ height }, mAppearance{ pTexture } {
	mpGameObject = ResourceManager::Instance().New<GameObject>("UI Rectangle");
	auto pTransformC = mpGameObject->Add<TransformComponent>();

	pTransformC->SetScale(glm::vec3{ width, height, 1.0f });

	auto pRenderC = mpGameObject->Add<RenderComponent>();
	pRenderC->SetRenderMode(RenderMode::UI);

	if (eCameraTag == CameraTag::ALL) {
		for (auto it = RenderEngine::Instance().CameraBegin();
			it != RenderEngine::Instance().CameraEnd(); ++it) {
			pRenderC->SetCamera(*it);
		}
	}

	auto pShader = ResourceManager::Instance().Retrieve<Shader>("Texture Shader");
	auto mat = new Material(pShader);

	mat->SetUniform("uSampler", pTexture);

	pRenderC->SetMaterial(mat);
	pRenderC->SetMesh(Primitives::Plane<Vertex::POSITION | Vertex::TEXTURE_COORD>());
}