#include "test-component.hpp"

#include <iostream>

#include "component.hpp"
#include "game-object.hpp"
#include "input-manager.hpp"
#include "resource-manager.hpp"
#include "to-string.hpp"
#include "transform-component.hpp"

void TestComponent::Start() {

}

void TestComponent::Update() {
    // all "if A is pressed, print such-and-such" should be placed in here

    ResourceManager& rm = ResourceManager::Instance();

    if (mIM.EventActive(Input::A_PRESSED)) {

        GameObject* pGO = rm.Retrieve<GameObject>("Box1");
        TransformComponent* pTransformC = pGO->Retrieve<TransformComponent>();


        std::cout << "Object space of Box 1 is \n" <<
            pTransformC->ObjectSpace() << std::endl;
    }

    if (mIM.EventActive(Input::B_PRESSED)) {
        GameObject* pGO = rm.Retrieve<GameObject>("Box2");
        TransformComponent* pTransformC = pGO->Retrieve<TransformComponent>();


        std::cout << "Object space of Box 2 is \n" <<
            pTransformC->ObjectSpace() << std::endl;
    }

    if (mIM.EventActive(Input::C_PRESSED)) {
        GameObject* pGO = rm.Retrieve<GameObject>("Stingray");
        TransformComponent* pTransformC = pGO->Retrieve<TransformComponent>();


        std::cout << "Object space of Stingray is \n" <<
            pTransformC->ObjectSpace() << std::endl;
    }
}

void TestComponent::ConstUpdate() const {
    
}

const char* TestComponent::Name() const {
    return "Test";
}

TestComponent::TestComponent(GameObject* pGO) : Component(pGO),
mIM{ InputManager::Instance() }  { }
    