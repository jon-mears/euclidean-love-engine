#include "scale-component.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "unit-transformation-component.hpp"

glm::mat4 ScaleComponent::ApplyRHS(glm::mat4 const& lhs) {
    return glm::scale(lhs, mScale);
}

glm::vec3 ScaleComponent::GetScale() {
    return mScale;
}

float ScaleComponent::GetScaleX() {
    return mScale.x;
}

float ScaleComponent::GetScaleY() {
    return mScale.y;
}

float ScaleComponent::GetScaleZ() {
    return mScale.z;
}

void ScaleComponent::SetScale(glm::vec3 const& new_scale) {
    mScale = new_scale;

    mLocalClean = false;
}

void ScaleComponent::SetScale(float new_scale) {
    mScale = glm::vec3{ new_scale, new_scale, new_scale };

    mLocalClean = false;
}

void ScaleComponent::SetScaleX(float new_x) {
    mScale.x = new_x;

    mLocalClean = false;
}

void ScaleComponent::SetScaleY(float new_y) {
    mScale.x = new_y;

    mLocalClean = false;
}

void ScaleComponent::SetScaleZ(float new_z) {
    mScale.x = new_z;

    mLocalClean = false;
}

void ScaleComponent::Start() {

}

void ScaleComponent::Update() {
    
}

void ScaleComponent::ConstUpdate() const {
    
}

const char* ScaleComponent::Name() const {
    return "Scale";
}

ScaleComponent::ScaleComponent(GameObject* pGO) :
    UnitTransformationComponent{ pGO }, mScale{ 1 } { }