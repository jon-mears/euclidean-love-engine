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
    virtual glm::mat4 Matrix(unsigned fTransformations) override;
    virtual glm::mat4 LocalMatrix(unsigned fTransformations =
    Transformation::ALL) override;
    virtual void ConstUpdate() const override;

    virtual const char* Name() override;

    RotationComponent(GameObject* pGO);
};
#endif