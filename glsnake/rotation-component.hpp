#ifndef ROTATION_COMPONENT_HPP
#define ROTATION_COMPONENT_HPP

#include "unit-transformation-component.hpp"
#include "glm/gtc/quaternion.hpp"

class GameObject;

class RotationComponent : public UnitTransformationComponent {
private:
    glm::vec3 mEuler;
    glm::quat mQuat;

    bool mEulerClean;
    bool mQuatClean;

public:
    virtual void Start() override;
    virtual void Update() override;
    virtual void ConstUpdate() const override;
    glm::mat4 ApplyRHS(glm::mat4 const& lhs);

    virtual const char* Name() const override;

    RotationComponent(GameObject* pGO);
};
#endif