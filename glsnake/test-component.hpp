#ifndef TEST_COMPONENT_HPP
#define TEST_COMPONENT_HPP

#include "component.hpp"
#include "input-manager.hpp"

class GameObject;

class TestComponent : public Component {
private:
    InputManager& mIM;
public:
    virtual void Start() override;
    virtual void Update() override;
    virtual void ConstUpdate() const override;
    virtual char const* Name() const override;

    TestComponent(GameObject* pGO);
};
#endif