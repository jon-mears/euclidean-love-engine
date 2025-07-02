#ifndef RENDER_COMPONENT_HPP
#define RENDER_COMPONENT_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "camera-component.hpp"
#include "component.hpp"
#include "layer.hpp"
#include "material.hpp"
#include "mesh.hpp"
#include "render-mode.hpp"
#include "projection.hpp"

class CameraComponent;
class GameObject;
class Projection;

class RenderComponent : public Component {
private:
    Material* mpMaterial{ nullptr };
    Mesh* mpMesh{ nullptr };
    CameraComponent* mpCameraC{ nullptr };
    Projection* mpProjection{ new NoProjection() };
    GLenum mePrimitiveType{ GL_TRIANGLES };
    RenderMode meRenderMode{RenderMode::NORMAL};
    Layer meLayer{ Layer::MAIN };


public:
    virtual void Start() override;
    virtual void Update() override;
    virtual void ConstUpdate() const override;

    inline void SetMaterial(Material* pMaterial) {
        mpMaterial = pMaterial;
    }

    inline Material* GetMaterial() {
        return mpMaterial;
    }

    inline void SetMesh(Mesh* pMesh) {
        mpMesh = pMesh;
    }

    inline Mesh* GetMesh() {
        return mpMesh;
    }

    inline void SetPrimitiveType(GLenum ePrimitiveType) {
        mePrimitiveType = ePrimitiveType;
    }

    inline GLenum GetPrimitiveType() {
        return mePrimitiveType;
    }

    inline void SetRenderMode(RenderMode eRenderMode) {
        meRenderMode = eRenderMode;
    }

    inline RenderMode GetRenderMode() {
        return meRenderMode;
    }

    inline int GetNumVertices() {
        if (mpMesh != nullptr) {
            return mpMesh->GetNumVertices();
        }

        else {
            return 0;
        }
    }

    inline void SetCamera(CameraComponent* pCameraC) {
        mpCameraC = pCameraC;
    }

    inline CameraComponent* GetCamera() {
        return mpCameraC;
    }

    inline Framebuffer* GetFramebuffer() {
        return mpCameraC->GetFramebuffer();
    }

    inline Shader* GetShader() {
        return mpMaterial->GetShader();
    }

    inline void SetProjection(Projection* pProjection) {
        mpProjection = pProjection;
    }

    inline Projection* GetProjection() {
        return mpProjection;
    }

    inline void SetLayer(Layer eLayer) {
        meLayer = eLayer;
    }

    inline Layer GetLayer() {
        return meLayer;
    }

    RenderComponent(GameObject* pGO);
};
#endif