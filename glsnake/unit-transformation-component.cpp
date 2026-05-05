#include "unit-transformation-component.hpp"

#include <glm/glm.hpp>

#include "component.hpp"

void UnitTransformationComponent::Start() {
    
}

void UnitTransformationComponent::Update() {
    
}

void UnitTransformationComponent::ConstUpdate() const {
    
}

glm::mat4 UnitTransformationComponent::InverseMatrix(unsigned fTransformations) {
    return glm::inverse(Matrix(fTransformations));
}

UnitTransformationComponent::UnitTransformationComponent(GameObject* pGO) : Component(pGO) { }
    