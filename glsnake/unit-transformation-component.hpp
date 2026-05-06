#ifndef UNIT_TRANSFORMATION_COMPONENT_HPP
#define UNIT_TRANSFORMATION_COMPONENT_HPP

#include <map>

#include <glm/glm.hpp>

#include "component.hpp"
class GameObject;

namespace Transformation {
    enum Transformation : unsigned {
        NONE = 0x00,
        SCALE = 0x01,
        ROTATE = 0x02,
        TRANSLATE = 0x04,
        ALL = 0x80
    };
}

class UnitTransformationComponent : public Component {
protected:
    std::map<unsigned, glm::mat4> mMatrix;
    glm::mat4 mLocalMatrix;
    std::map<unsigned, bool> mClean;
    bool mLocalClean;
    UnitTransformationComponent* mpParent;

    unsigned mfType;

public:
    virtual void Start() override;
    virtual void Update() override;
    virtual void ConstUpdate() const override;

    // this returns the local matrix multiplied by all parent matrices
    virtual glm::mat4 Matrix();
    virtual glm::mat4 Matrix(unsigned fTransformations);

    // this returns just the local matrix
    virtual glm::mat4 LocalMatrix() = 0;

    virtual glm::mat4 InverseMatrix(unsigned fTransformations =
        Transformation::ALL);

    UnitTransformationComponent(GameObject* pGO);

    virtual ~UnitTransformationComponent() = default;
};
#endif