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

UIRectangle::UIRectangle(float width, float height, Color color, CameraTag eCameraTag) : GameObject(), mWidth{ width }, mHeight{ height }, mAppearance{ color } {
	ResourceManager& rm = ResourceManager::Instance();

	auto pTransformC = Add<TransformComponent>();

	pTransformC->SetScale(glm::vec3{ width, height, 1.0f });
	
	auto pRenderC = Add<RenderComponent>();
	pRenderC->SetRenderMode(RenderMode::UI);

	pRenderC->SetProjection(new AspectProjection());

	if (eCameraTag == CameraTag::ALL) {
		for (auto it = RenderEngine::Instance().CameraBegin();
			it != RenderEngine::Instance().CameraEnd(); ++it) {
			pRenderC->SetCamera(*it);
		}
	}

	auto pShader = rm.Retrieve<Shader>("Color Shader");
	auto mat = new Material(pShader);

	mat->SetUniform("uColor", color.value);

	pRenderC->SetMaterial(mat);
	pRenderC->SetMesh(Primitives::Plane<Vertex::POSITION>());
}

UIRectangle::UIRectangle(float width, float height, Texture2D* pTexture,
	CameraTag eCameraTag) : mWidth{ width }, mHeight{ height }, mAppearance{ pTexture } {
	ResourceManager& rm = ResourceManager::Instance();

	auto pTransformC = Add<TransformComponent>();

	pTransformC->SetScale(glm::vec3{ width, height, 1.0f });

	auto pRenderC = Add<RenderComponent>();
	pRenderC->SetRenderMode(RenderMode::UI);

	pRenderC->SetProjection(new AspectProjection());

	if (eCameraTag == CameraTag::ALL) {
		for (auto it = RenderEngine::Instance().CameraBegin();
			it != RenderEngine::Instance().CameraEnd(); ++it) {
			pRenderC->SetCamera(*it);
		}
	}

	auto pShader = rm.Retrieve<Shader>("Texture Shader");
	auto mat = new Material(pShader);

	mat->SetUniform("uSampler", pTexture);
	mat->SetUniform("uColor", glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f });

	pRenderC->SetMaterial(mat);
	pRenderC->SetMesh(Primitives::Plane<Vertex::POSITION | Vertex::TEXTURE_COORD>());
}