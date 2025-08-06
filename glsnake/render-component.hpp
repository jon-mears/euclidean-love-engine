#ifndef RENDER_COMPONENT_HPP
#define RENDER_COMPONENT_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera-component.hpp"
#include "component.hpp"
#include "game-object.hpp"
#include "layer.hpp"
#include "material.hpp"
#include "mesh.hpp"
#include "projection.hpp"
#include "render-mode.hpp"

class RenderComponent : public Component {
public:
    RenderComponent(GameObject* GO);

    virtual void Start() override;
    virtual void Update() override;
    virtual void ConstUpdate() const override;

    virtual char const* Name() const override;

    ::Material* Material() const noexcept;

    void SetMaterial(::Material* material) noexcept;

    ::Mesh* Mesh() const noexcept;

    void SetMesh(::Mesh* mesh) noexcept;

    GLenum PrimitiveType() const noexcept;

    void SetPrimitiveType(GLenum primitive_type) noexcept;

    ::RenderMode RenderMode() const noexcept;

    void SetRenderMode(::RenderMode render_mode) noexcept;

    CameraComponent* Camera() const noexcept;

    void SetCamera(CameraComponent* camera) noexcept;

    ::Projection* Projection() const noexcept;

    void SetProjection(::Projection* projection) noexcept;

    ::Layer Layer() const noexcept;

    void SetLayer(::Layer layer) noexcept;

private:
    ::Material* mpMaterial;
    ::Mesh* mpMesh;
    CameraComponent* mpCameraC;
    ::Projection* mpProjection;
    GLenum mPrimitiveType;
    ::RenderMode mRenderMode;
    ::Layer mLayer;
};
#endif