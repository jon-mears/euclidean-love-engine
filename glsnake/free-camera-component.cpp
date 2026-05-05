#include "free-camera-component.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "component.hpp"
#include "input-manager.hpp"
#include "render-engine.hpp"
#include "transform-component.hpp"

class CameraComponent;

FreeCameraComponent::FreeCameraComponent(GameObject* GO) :
    CameraComponent{ GO }, mTheta{ 0 }, mPhi{ 0 }, mRho{ 0 }, mTarget{ 0 },
    mTumbleAmplitude{ 0.01f }, mTrackAmplitude{ 0.001f },
    mDollyAmplitude{ 0.01f }
{ }

void FreeCameraComponent::Start() {
    auto& re{ RenderEngine::Instance() };

    mpTransform = Get<TransformComponent>();
    mRho = glm::length(mTarget - mpTransform->Position());

    re.AddCamera(this);
}

void FreeCameraComponent::Update() {
    auto& im{ InputManager::Instance() };

    auto pos_updated{ false };

    if (im.EventActive(Input::ORBITING)) {
        mTheta -= im.RelativeAxis(Input::HORIZONTAL) * mTumbleAmplitude;
        mPhi -= im.RelativeAxis(Input::VERTICAL) * mTumbleAmplitude;

        auto q1{ glm::
            quat(mTheta, glm::vec3(0, 1, 0)) };
        auto q2{ glm::angleAxis(mPhi, glm::vec3(1, 0, 0)) };

        mpTransform->SetQuatRotation(q1 * q2);
        mpTransform->UpdateEuler();
        mpTransform->UpdateSpace();

        pos_updated = true;
    }

    auto scroll_amount{ im.RelativeAxis(Input::SCROLL) };

    if (scroll_amount != 0) {
        mRho -= scroll_amount * mDollyAmplitude;

        pos_updated = true;
    }

    if (im.EventActive(Input::PANNING)) {
        auto xdelta{ im.RelativeAxis(Input::HORIZONTAL) * mTrackAmplitude };
        auto ydelta{ im.RelativeAxis(Input::VERTICAL) * mTrackAmplitude };

        auto local_x{ mpTransform->X() };
        auto local_y{ mpTransform->Y() };

        mTarget += -xdelta * local_x + ydelta * local_y;

        pos_updated = true;
    }

    if (pos_updated) {
        mpTransform->SetPosition(mTarget + mRho * mpTransform->Z());
    }
}

void FreeCameraComponent::ConstUpdate() const { }

char const* FreeCameraComponent::Name() const {
    return "FreeCamera";
}