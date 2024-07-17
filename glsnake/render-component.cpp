#include "component.hpp"
#include "render-command.hpp"
#include "render-component.hpp"
#include "render-engine.hpp"

void RenderComponent::Start() {
    RenderEngine::Instance().AddCommand(new RenderCommand(this));
}

void RenderComponent::Update() {
    
}

void RenderComponent::ConstUpdate() const {
    
}

RenderComponent::RenderComponent(GameObject* pGO) : Component(pGO) { }
    