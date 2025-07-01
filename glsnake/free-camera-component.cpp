#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

#include "camera-component.hpp"
#include "free-camera-component.hpp"
#include "component.hpp"
#include "input-manager.hpp"
#include "transform-component.hpp"
#include "math-3d.hpp"

void FreeCameraComponent::Update() {
    bool posUpdated = false;

    if (InputManager::Instance().EventActive(Input::ORBITING)) {
        mTheta -= InputManager::Instance().RelativeAxis(Input::HORIZONTAL) *
            kTumbleAmplitude;
        mPhi -= InputManager::Instance().RelativeAxis(Input::VERTICAL) *
            kTumbleAmplitude;

        glm::quat q1 = glm::angleAxis(mTheta, glm::vec3(0, 1, 0));
        glm::quat q2 = glm::angleAxis(mPhi, glm::vec3(1, 0, 0));
        mpTransform->SetQuaternionRotation(q1 * q2);
        mpTransform->UpdateEulerRotation();
        mpTransform->UpdateLocalAxes();

        posUpdated = true;
    }

    double scrollAmount = InputManager::Instance().RelativeAxis(Input::SCROLL);

    if (scrollAmount != 0) {
        mRho -= scrollAmount * kDollyAmplitude;
        posUpdated = true;
    }

    if (InputManager::Instance().EventActive(Input::PANNING)) {
        float xdelta = InputManager::Instance().RelativeAxis(Input::HORIZONTAL) * kTrackAmplitude;
        float ydelta = InputManager::Instance().RelativeAxis(Input::VERTICAL) * kTrackAmplitude;

        glm::vec3 localX = mpTransform->LocalX();
        glm::vec3 localY = mpTransform->LocalY();

        mTarget += -xdelta * localX + ydelta * localY;

        posUpdated = true;
    }

    if (posUpdated) {
        mpTransform->SetPosition(mTarget + mRho * mpTransform->LocalZ());
        //mpTransform->SetPosition(Math3D::SphericalCoordinatesRad(mTarget, mPhi, mTheta, mRho));
    }
}

void FreeCameraComponent::ConstUpdate() const {

}

FreeCameraComponent::FreeCameraComponent(GameObject* pGO) : CameraComponent(pGO) { }
    