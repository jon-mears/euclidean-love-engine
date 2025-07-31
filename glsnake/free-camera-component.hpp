#ifndef FREE_CAMERA_COMPONENT_HPP
#define FREE_CAMERA_COMPONENT_HPP

#include <glm/glm.hpp>

#include "camera-component.hpp"
#include "component.hpp"
class GameObject;

class FreeCameraComponent : public CameraComponent {
private:

    float mTheta{ 0 };
    float mPhi{ 0 };
    float mRho{ 0 };
    glm::vec3 mTarget = glm::vec3{ 0 };

    static constexpr float kTumbleAmplitude{ 0.01 };
    static constexpr float kTrackAmplitude{ 0.001 };
    static constexpr float kDollyAmplitude{ 0.01 };

public:
    virtual void Start() override;
    virtual void Update() override;
    virtual void ConstUpdate() const override;

    FreeCameraComponent(GameObject* pGO);

    inline const char* Name() const {
        return "FreeCamera";
    }
};
#endif