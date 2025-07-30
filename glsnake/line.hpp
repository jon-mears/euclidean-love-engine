#ifndef LINE_HPP
#define LINE_HPP

#include <iostream>

#include "camera-component.hpp"
#include "color.hpp"
#include "game-object.hpp"
#include "primitives.hpp"
#include "layer.hpp"
#include "render-engine.hpp"
#include "resource-manager.hpp"
#include "render-component.hpp"
#include "shader.hpp"
#include "transform-component.hpp"
#include "material.hpp"
#include "projection.hpp"
	
template <int x1, int y1, int z1,
		  int x2, int y2, int z2>
class Line : public GameObject {
private:
	Color mColor;

public:
	Line(CameraComponent* pCameraC, Color c = Color::WHITE) : GameObject(),
		mColor{ c } {
		ResourceManager& rm = ResourceManager::Instance();
		RenderEngine& re = RenderEngine::Instance();

		auto pTransformC = Add<TransformComponent>();

		auto pRenderC = Add<RenderComponent>();

		pRenderC->SetProjection(new Perspective());

		pRenderC->SetCamera(pCameraC);
		pRenderC->SetLayer(Layer::TOP);
		pRenderC->SetPrimitiveType(GL_LINES);

		pRenderC->SetMesh(Primitives::Line<x1, y1, z1, x2, y2, z2>());

		auto pShader = rm.Retrieve<Shader>("Color Shader");
		auto pMat = new Material(pShader);

		pMat->SetUniform("uColor", c.value);
		pRenderC->SetMaterial(pMat);
	}
};
#endif