#ifndef UNIT_TRANSFORMATION_COMPONENT_HPP
#define UNIT_TRANSFORMATION_COMPONENT_HPP

#include <map>

#include <glm/glm.hpp>

#include "component.hpp"
class GameObject;

namespace Transformation {
    enum Transformation : unsigned {
        SCALE = 0x01,
        ROTATE = 0x02,
        TRANSLATE = 0x04
    };
}

class UnitTransformationComponent : public Component {
private:
    std::map<unsigned, glm::mat4> mMatrix;
    std::map<unsigned, bool> mClean;

public:
    virtual void Start() override;
    virtual void Update() override;
    virtual void ConstUpdate() const override;

    virtual glm::mat4 Matrix(unsigned fTransformations =
        Transformation::SCALE |
        Transformation::ROTATE |
        Transformation::TRANSLATE) = 0;

    virtual glm::mat4 InverseMatrix(unsigned fTransformations =
        Transformation::SCALE |
        Transformation::ROTATE |
        Transformation::TRANSLATE);

    UnitTransformationComponent(GameObject* pGO);
};
#endif