#ifndef SCALE_COMPONENT_HPP
#define SCALE_COMPONENT_HPP

#include "component.hpp"
class GameObject;

class ScaleComponent : public Component {
private:

public:
    virtual void Start() override;
    virtual void Update() override;
    virtual void ConstUpdate() const override;
    virtual const char* Name() const override;

    ScaleComponent(GameObject* pGO);
};
#endif