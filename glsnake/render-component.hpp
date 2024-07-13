#ifndef RENDER_COMPONENT_HPP
#define RENDER_COMPONENT_HPP

#include "component.hpp"
class GameObject;

class RenderComponent : public Component {
private:

public:
    virtual void Start() override;
    virtual void Update() override;
    virtual void ConstUpdate() const override;

    RenderComponent(GameObject* pGO);
};
#endif