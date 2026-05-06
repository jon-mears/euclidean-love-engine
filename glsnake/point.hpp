#ifndef POINT_HPP
#define POINT_HPP

#include "camera-component.hpp"
#include "color.hpp"
#include "game-object.hpp"
#include "layer.hpp"
#include "primitives.hpp"
#include "projection.hpp"
#include "render-component.hpp"
#include "resource-manager.hpp"
#include "transform-component.hpp"

class Point : public GameObject {
public:
	Point(CameraComponent* pCameraC, Color c = Color::WHITE) : GameObject() {
		ResourceManager& rm = ResourceManager::Instance();

		auto pTransformC = Add<TransformComponent>();
		auto pRenderC = Add<RenderComponent>();

		pRenderC->SetProjection(new Perspective());
		pRenderC->SetCamera(pCameraC);
		pRenderC->SetLayer(Layer::TOP);
		pRenderC->SetPrimitiveType(GL_POINTS);
		pRenderC->SetMesh(Primitives::Point());

		auto pShader{ rm.Retrieve<Shader>("Color Shader") };
		auto pMat{ new Material(pShader) };

		pMat->SetUniform("uColor", c.value);
		pRenderC->SetMaterial(pMat);
	}
};

#endif