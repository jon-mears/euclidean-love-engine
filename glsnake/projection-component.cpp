#include "projection-component.hpp"
#include "game-object.hpp"
#include "component.hpp"

ProjectionComponent::ProjectionComponent(GameObject* pGO) : Component{ pGO } { }

void ProjectionComponent::Start() { }
void ProjectionComponent::Update() { }
void ProjectionComponent::ConstUpdate() const { }