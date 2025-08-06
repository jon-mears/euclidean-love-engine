#ifndef FREE_CAMERA_COMPONENT_HPP
#define FREE_CAMERA_COMPONENT_HPP

#include <glm/glm.hpp>

#include "camera-component.hpp"

class GameObject;

class FreeCameraComponent : public CameraComponent {
public:
    FreeCameraComponent(GameObject* GO);

    virtual void Start() override;
    virtual void Update() override;
    virtual void ConstUpdate() const override;

    char const* Name() const override;

private:
    float mTheta;
    float mPhi;
    float mRho;

    glm::vec3 mTarget;

    float mTumbleAmplitude;
    float mTrackAmplitude;
    float mDollyAmplitude;
};
#endif