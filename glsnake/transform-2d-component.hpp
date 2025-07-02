//#ifndef TRANSFORM_2D_COMPONENT_HPP
//#define TRANSFORM_2D_COMPONENT_HPP
//
//#include "component.hpp"
//#include "transform-component.hpp"
//class GameObject;
//
//#include <vector>
//
//#include <glm/glm.hpp>
//
//class Transform2DComponent : public Component {
//private:
//    glm::vec2 mWorldPosition;
//    glm::vec2 mLocalPosition;
//    glm::vec2 mLocalOrigin{ 0 };
//
//    float mRotation;
//
//    glm::vec2 mScale;
//
//    glm::vec2 mLocalX;
//    glm::vec2 mLocalY;
//
//    Space* mpObjectSpace{ nullptr };
//
//    Transform2DComponent* mpParent{ nullptr };
//    std::vector<Transform2DComponent*> mChildren{};
//
//public:
//    virtual void Update() override;
//    virtual void ConstUpdate() const override;
//
//    Transform2DComponent(GameObject* pGO);
//    void SetPosition(const glm::vec2& new_position, Space* pSpace = Space::World());
//    void Translate(const glm::vec2& trans, Space* pSpace = Space::World());
//
//    void SetRotation(float rad);
//    void 
//};
//
//#endif