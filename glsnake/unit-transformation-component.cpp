#include "unit-transformation-component.hpp"

#include <glm/glm.hpp>

#include "component.hpp"

void UnitTransformationComponent::Start() {
    
}

void UnitTransformationComponent::Update() {
    
}

void UnitTransformationComponent::ConstUpdate() const {
    
}

glm::mat4 UnitTransformationComponent::Matrix(unsigned fTransformations) {
    if (!mClean[fTransformations]) {
        mClean[fTransformations] = true;
        mMatrix[fTransformations] = mpParent->Matrix(fTransformations);
        if (mfType & fTransformations ||
            fTransformations == Transformation::ALL) {
            mMatrix[fTransformations] = ApplyRHS(mMatrix[fTransformations]);
        }
    }
    return mMatrix[fTransformations];
}

glm::mat4 UnitTransformationComponent::LocalMatrix() {
    if (!mLocalClean) {
        mLocalClean = true;
        mLocalMatrix = ApplyRHS(glm::mat4{ 1 });
    }
    return mLocalMatrix;
}

// avoids the if-statement if _all_ transformations are desired (which is most
// common)
glm::mat4 UnitTransformationComponent::Matrix() {
    if (!mClean[Transformation::ALL]) {
        mClean[Transformation::ALL] = true;
        mMatrix[Transformation::ALL] = ApplyRHS(mpParent->Matrix());
    }
    return mMatrix[Transformation::ALL];
}

glm::mat4 UnitTransformationComponent::InverseMatrix(unsigned fTransformations) {
    return glm::inverse(Matrix(fTransformations));
}

UnitTransformationComponent::UnitTransformationComponent(GameObject* pGO) : Component(pGO) { }
    