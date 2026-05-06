#include "rotation-component.hpp"

void RotationComponent::Start() {
    
}

void RotationComponent::Update() {
    
}

void RotationComponent::ConstUpdate() const {
    
}

glm::mat4 RotationComponent::LocalMatrix(unsigned fTransformations) {
    if (mLocalClean) {
        return mLocalMatrix;
    }
    else {
        mLocalMatrix = glm::mat4{ 1 };
    }
}

RotationComponent::RotationComponent(GameObject* pGO) :
    UnitTransformationComponent(pGO) { }
    