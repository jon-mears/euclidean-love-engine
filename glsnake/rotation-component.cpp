#include "rotation-component.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>

void RotationComponent::Start() {
    
}

void RotationComponent::Update() {
    
}

void RotationComponent::ConstUpdate() const {
    
}

// I like this idea of an apply method... implies that the transformation is
// _applied_ to the parameter matrix but not _necessarily_ that a matrix
// multiplication occurs.
glm::mat4 RotationComponent::ApplyRHS(glm::mat4 const& lhs) {
    if (mQuatClean) {
        return lhs * glm::toMat4(mQuat);
    }
    else {
        glm::mat4 result;
        result = glm::rotate(lhs, glm::radians(mEuler.y),
            glm::vec3{ 0, 1, 0 });
        result = glm::rotate(mLocalMatrix, glm::radians(mEuler.x),
            glm::vec3{ 1, 0, 0 });
        result = glm::rotate(mLocalMatrix, glm::radians(mEuler.z),
            glm::vec3{ 0, 0, 1 });

        return result;
    }
}

const char* RotationComponent::Name() const {
    return "Rotation";
}

RotationComponent::RotationComponent(GameObject* pGO) :
    UnitTransformationComponent(pGO) { }