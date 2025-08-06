#include "render-component.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera-component.hpp"
#include "component.hpp"
#include "game-object.hpp"
#include "layer.hpp"
#include "material.hpp"
#include "mesh.hpp"
#include "projection.hpp"
#include "render-command.hpp"
#include "render-engine.hpp"
#include "render-mode.hpp"

RenderComponent::RenderComponent(GameObject* GO) :
    Component{ GO }, mpMaterial{ nullptr }, mpMesh{ nullptr },
    mpCameraC{ nullptr }, mpProjection{ nullptr },
    mPrimitiveType{ GL_TRIANGLES }, mRenderMode{ ::RenderMode::NORMAL },
    mLayer{ ::Layer::MAIN }
{ }

void RenderComponent::Start() {
    auto& re{ RenderEngine::Instance() };

    re.AddCommand(new RenderCommand(this));
}

void RenderComponent::Update() { }

void RenderComponent::ConstUpdate() const { }

char const* RenderComponent::Name() const {
    return "Render";
}

::Material* RenderComponent::Material() const noexcept {
    return mpMaterial;
}

void RenderComponent::SetMaterial(::Material* material) noexcept {
    mpMaterial = material;
}

::Mesh* RenderComponent::Mesh() const noexcept {
    return mpMesh;
}

void RenderComponent::SetMesh(::Mesh* mesh) noexcept {
    mpMesh = mesh;
}

GLenum RenderComponent::PrimitiveType() const noexcept {
    return mPrimitiveType;
}

void RenderComponent::SetPrimitiveType(GLenum primitive_type) noexcept {
    mPrimitiveType = primitive_type;
}

::RenderMode RenderComponent::RenderMode() const noexcept {
    return mRenderMode;
}

void RenderComponent::SetRenderMode(::RenderMode render_mode) noexcept {
    mRenderMode = render_mode;

    if (mRenderMode == RenderMode::UI) {
        mLayer = Layer::TOP;
    }
    else {
        mLayer = Layer::MAIN;
    }
}

CameraComponent* RenderComponent::Camera() const noexcept {
    return mpCameraC;
}

void RenderComponent::SetCamera(CameraComponent* camera) noexcept {
    mpCameraC = camera;
}

::Projection* RenderComponent::Projection() const noexcept {
    return mpProjection;
}

void RenderComponent::SetProjection(::Projection* projection) noexcept {
    mpProjection = projection;
}

::Layer RenderComponent::Layer() const noexcept {
    return mLayer;
}

void RenderComponent::SetLayer(::Layer layer) noexcept {
    mLayer = layer;
}