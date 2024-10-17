#ifndef HAT_COMPONENT_HPP
#define HAT_COMPONENT_HPP

#include "component.hpp"
class GameObject;

class HatComponent : public Component {
private:

public:
    virtual void Start() override;
    virtual void Update() override;
    virtual void ConstUpdate() const override;

    HatComponent(GameObject* pGO);
};
#endif