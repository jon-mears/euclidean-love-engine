#ifndef SCALE_COMPONENT_HPP
#define SCALE_COMPONENT_HPP

#include "unit-transformation-component.hpp"
class GameObject;

class ScaleComponent : public UnitTransformationComponent {
private:

    glm::vec3 mScale;

public:
    glm::vec3 GetScale();
    float GetScaleX();
    float GetScaleY();
    float GetScaleZ();

    void SetScale(glm::vec3 const& new_scale);
    void SetScale(float new_scale);
    void SetScaleX(float new_x);
    void SetScaleY(float new_y);
    void SetScaleZ(float new_z);

    virtual glm::mat4 ApplyRHS(glm::mat4 const& lhs) override;

    virtual void Start() override;
    virtual void Update() override;
    virtual void ConstUpdate() const override;
    virtual const char* Name() const override;

    ScaleComponent(GameObject* pGO);
};
#endif