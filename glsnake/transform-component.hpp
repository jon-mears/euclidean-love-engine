#ifndef TRANSFORM_COMPONENT_HPP
#define TRANSFORM_COMPONENT_HPP

#include <algorithm>
#include <iostream>
#include <vector>

#include "angles.hpp"
#include "component.hpp"
#include "space.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GameObject;
class GLFWwindow;

class TransformComponent : public Component {
public:
	TransformComponent(GameObject* GO);

	virtual void Start() override;
	virtual void Update() override;
	virtual void ConstUpdate() const override;

	virtual char const* Name() const override;

	// Position

	glm::vec3 Position(Space const& space);
	glm::vec3 Position(Space::Label space = Space::LOCAL);

	void SetPosition(glm::vec3 const& new_position, Space const& space);
	void SetPosition(float x, float y, float z, Space const& space);

	void SetPositionExcl(glm::vec3 const& new_position, Space const& space);
	void SetPositionExcl(float x, float y, float z, Space const& space);

	void SetPosition(
		glm::vec3 const& new_position, Space::Label space = Space::LOCAL
	);
	void SetPosition(
		float x, float y, float z, Space::Label space = Space::LOCAL
	);

	void SetPositionExcl(
		glm::vec3 const& new_position, Space::Label space = Space::LOCAL
	);
	void SetPositionExcl(
		float x, float y, float z, Space::Label space = Space::LOCAL
	);

	void SetPositionX(float x, Space const& space);
	void SetPositionX(float x, Space::Label space = Space::Label::LOCAL);

	void SetPositionXExcl(float x, Space const& space);
	void SetPositionXExcl(float x, Space::Label space = Space::Label::LOCAL);

	void SetPositionY(float y, Space const& space);
	void SetPositionY(float y, Space::Label space = Space::Label::LOCAL);

	void SetPositionYExcl(float y, Space const& space);
	void SetPositionYExcl(float y, Space::Label space = Space::Label::LOCAL);

	void SetPositionZ(float z, Space const& space);
	void SetPositionZ(float z, Space::Label space = Space::Label::LOCAL);

	void SetPositionZExcl(float z, Space const& space);
	void SetPositionZExcl(float z, Space::Label space = Space::Label::LOCAL);

	void Translate(glm::vec3 const& trans, Space const& space);
	void Translate(float x, float y, float z, Space const& space);
	void Translate(glm::vec3 const& trans, Space::Label space = Space::LOCAL);
	void Translate(float x, float y, float z, Space::Label space = Space::LOCAL);

	void TranslateExcl(glm::vec3 const& trans, Space const& space);
	void TranslateExcl(float x, float y, float z, Space const& space);
	void TranslateExcl(glm::vec3 const& trans, Space::Label space = Space::LOCAL);
	void TranslateExcl(float x, float y, float z, Space::Label space = Space::LOCAL);

	void TranslateX(float x, Space const& space);
	void TranslateX(float x, Space::Label space = Space::LOCAL);

	void TranslateXExcl(float x, Space const& space);
	void TranslateXExcl(float x, Space::Label space = Space::LOCAL);

	void TranslateY(float y, Space const& space);
	void TranslateY(float y, Space::Label space = Space::LOCAL);
	
	void TranslateYExcl(float y, Space const& space);
	void TranslateYExcl(float y, Space::Label space = Space::LOCAL);

	void TranslateZ(float z, Space const& space);
	void TranslateZ(float z, Space::Label space = Space::LOCAL);

	void TranslateZExcl(float z, Space const& space);
	void TranslateZExcl(float z, Space::Label space = Space::LOCAL);

	// Euler Rotation

	glm::vec3 EulerRotation(Space const& space);
	glm::vec3 EulerRotation(Space::Label space = Space::WORLD);

	void SetEulerRotation(
		Degrees x, Degrees y, Degrees z, Space const& space
	);
	void SetEulerRotation(
		Degrees x, Degrees y, Degrees z,
		Space::Label space = Space::OBJECT_WORLD
	);
	void SetEulerRotation(
		Radians x, Radians y, Radians z, Space const& space
	);
	void SetEulerRotation(
		Radians x, Radians y, Radians z,
		Space::Label space = Space::OBJECT_WORLD
	);

	void SetEulerRotationExcl(
		Degrees x, Degrees y, Degrees z, Space const& space
	);
	void SetEulerRotationExcl(
		Degrees x, Degrees y, Degrees z,
		Space::Label space = Space::OBJECT_WORLD
	);
	void SetEulerRotationExcl(
		Radians x, Radians y, Radians z, Space const& space
	);
	void SetEulerRotationExcl(
		Radians x, Radians y, Radians z,
		Space::Label space = Space::OBJECT_WORLD
	);

	void SetEulerRotationX(Degrees x, Space const& space);
	void SetEulerRotationX(
		Degrees x, Space::Label space = Space::Label::OBJECT_WORLD
	);

	void SetEulerRotationXExcl(Degrees x, Space const& space);
	void SetEulerRotationXExcl(
		Degrees x, Space::Label space = Space::Label::OBJECT_WORLD
	);

	void SetEulerRotationX(Radians x, Space const& space);
	void SetEulerRotationX(
		Radians x, Space::Label space = Space::Label::OBJECT_WORLD
	);

	void SetEulerRotationXExcl(Radians x, Space const& space);
	void SetEulerRotationXExcl(
		Radians x, Space::Label space = Space::Label::OBJECT_WORLD
	);

	void SetEulerRotationY(Degrees y, Space const& space);
	void SetEulerRotationY(
		Degrees y, Space::Label space = Space::Label::OBJECT_WORLD
	);

	void SetEulerRotationYExcl(Degrees y, Space const& space);
	void SetEulerRotationYExcl(
		Degrees y, Space::Label space = Space::Label::OBJECT_WORLD
	);

	void SetEulerRotationY(Radians y, Space const& space);
	void SetEulerRotationY(
		Radians y, Space::Label space = Space::Label::OBJECT_WORLD
	);

	void SetEulerRotationYExcl(Radians y, Space const& space);
	void SetEulerRotationYExcl(
		Radians y, Space::Label space = Space::Label::OBJECT_WORLD
	);

	void SetEulerRotationZ(Degrees z, Space const& space);
	void SetEulerRotationZ(
		Degrees z, Space::Label space = Space::Label::OBJECT_WORLD
	);

	void SetEulerRotationZExcl(Degrees z, Space const& space);
	void SetEulerRotationZExcl(
		Degrees z, Space::Label space = Space::Label::OBJECT_WORLD
	);

	void SetEulerRotationZ(Radians z, Space const& space);
	void SetEulerRotationZ(
		Radians z, Space::Label space = Space::Label::OBJECT_WORLD
	);

	void SetEulerRotationZExcl(Radians z, Space const& space);
	void SetEulerRotationZExcl(
		Radians z, Space::Label space = Space::Label::OBJECT_WORLD
	);

	void EulerRotate(Degrees x, Degrees y, Degrees z, Space const& space);
	void EulerRotate(
		Degrees x, Degrees y, Degrees z,
		Space::Label space = Space::Label::OBJECT_WORLD
	);

	void EulerRotateExcl(Degrees x, Degrees y, Degrees z, Space const& space);
	void EulerRotateExcl(
		Degrees x, Degrees y, Degrees z,
		Space::Label space = Space::Label::OBJECT_WORLD
	);
			
	void EulerRotate(Radians x, Radians y, Radians z, Space const& space);
	void EulerRotate(
		Radians x, Radians y, Radians z,
		Space::Label space = Space::Label::OBJECT_WORLD
	);

	void EulerRotateExcl(Radians x, Radians y, Radians z, Space const& space);
	void EulerRotateExcl(
		Radians x, Radians y, Radians z,
		Space::Label space = Space::Label::OBJECT_WORLD
	);

	void EulerRotateX(Degrees x, Space const& space);
	void EulerRotateX(
		Degrees x, Space::Label space = Space::Label::OBJECT_WORLD
	);

	void EulerRotateXExcl(Degrees x, Space const& space);
	void EulerRotateXExcl(
		Degrees x, Space::Label space = Space::Label::OBJECT_WORLD
	);

	void EulerRotateX(Radians x, Space const& space);
	void EulerRotateX(
		Radians x, Space::Label space = Space::Label::OBJECT_WORLD
	);

	void EulerRotateXExcl(Radians x, Space const& space);
	void EulerRotateXExcl(
		Radians x, Space::Label space = Space::Label::OBJECT_WORLD
	);

	void EulerRotateY(Degrees y, Space const& space);
	void EulerRotateY(
		Degrees y, Space::Label space = Space::Label::OBJECT_WORLD
	);

	void EulerRotateYExcl(Degrees y, Space const& space);
	void EulerRotateYExcl(
		Degrees y, Space::Label space = Space::Label::OBJECT_WORLD
	);

	void EulerRotateY(Radians y, Space const& space);
	void EulerRotateY(
		Radians y, Space::Label space = Space::Label::OBJECT_WORLD
	);

	void EulerRotateYExcl(Radians y, Space const& space);
	void EulerRotateYExcl(
		Radians y, Space::Label space = Space::Label::OBJECT_WORLD
	);

	void EulerRotateZ(Degrees z, Space const& space);
	void EulerRotateZ(
		Degrees z, Space::Label space = Space::Label::OBJECT_WORLD
	);

	void EulerRotateZExcl(Degrees z, Space const& space);
	void EulerRotateZExcl(
		Degrees z, Space::Label space = Space::Label::OBJECT_WORLD
	);

	void EulerRotateZ(Radians z, Space const& space);
	void EulerRotateZ(
		Radians z, Space::Label space = Space::Label::OBJECT_WORLD
	);

	void EulerRotateZExcl(Radians z, Space const& space);
	void EulerRotateZExcl(
		Radians z, Space::Label space = Space::Label::OBJECT_WORLD
	);

	void MakeEulerClean();
	void UpdateEuler();

	// Quaternion Rotation

	glm::quat QuatRotation() noexcept;

	void SetQuatRotation(glm::quat const& quat_rotation);

	void QuatRotate(glm::quat const& q);

	void MakeQuatClean();

	// Code for this function was found from an external source.
	void UpdateQuat();

	// Angle Axis Rotation

	//template <typename A>
	//glm::vec4 AngleAxisRotation(Space const& space) noexcept;

	//template <typename A>
	//glm::vec4 AngleAxisRotation(
	//	Space::Label space = Space::Label::OBJECT_WORLD
	//) noexcept;	

	//void SetAngleAxisRotation(
	//	Degrees angle, glm::vec3 const& axis, Space const& space
	//);
	//void SetAngleAxisRotation(
	//	Degrees angle, glm::vec3 const& axis,
	//	::Space::Label space = ::Space::Label::OBJECT_WORLD
	//);

	//void SetAngleAxisRotationExcl(
	//	Degrees angle, glm::vec3 const& axis, ::Space const& space
	//);
	//void SetAngleAxisRotationExcl(
	//	Degrees angle, glm::vec3 const& axis,
	//	::Space::Label space = ::Space::Label::OBJECT_WORLD
	//);

	//void SetAngleAxisRotation(
	//	Radians angle, glm::vec3 const& axis, ::Space const& space
	//);
	//void SetAngleAxisRotation(
	//	Radians angle, glm::vec3 const& axis,
	//	::Space::Label space = ::Space::Label::OBJECT_WORLD
	//);

	//void SetAngleAxisRotationExcl(
	//	Radians angle, glm::vec3 const& axis, ::Space const& space
	//);
	//void SetAngleAxisRotationExcl(
	//	Radians angle, glm::vec3 const& axis,
	//	::Space::Label space = ::Space::Label::OBJECT_WORLD
	//);

	//// Scale

	//glm::vec3 Scale(::Space const& space) const noexcept;
	glm::vec3 Scale(
		::Space::Label space = ::Space::Label::OBJECT
	);

	//void SetScale(glm::vec3 const& new_scale, ::Space const& space);
	//void SetScale(float x, float y, float z, ::Space const& space);

	//void SetScaleExcl(glm::vec3 const& new_scale, ::Space const& space);
	//void SetScaleExcl(float x, float y, float z, ::Space const& space);

	void SetScale(
		glm::vec3 const& new_scale, ::Space::Label space = ::Space::OBJECT
	);
	//void SetScale(
	//	float x, float y, float z, ::Space::Label space = ::Space::LOCAL
	//);

	//void SetScaleExcl(
	//	glm::vec3 const& new_scale, ::Space::Label space = ::Space::LOCAL
	//);
	//void SetScaleExcl(
	//	float x, float y, float z, ::Space::Label space = ::Space::LOCAL
	//);

	//void SetScaleX(float x, ::Space const& space);
	//void SetScaleX(float x, ::Space::Label space = ::Space::Label::LOCAL);

	//void SetScaleXExcl(float x, ::Space const& space);
	//void SetScaleXExcl(float x, ::Space::Label space = ::Space::Label::LOCAL);

	//void SetScaleY(float y, ::Space const& space);
	//void SetScaleY(float y, ::Space::Label space = ::Space::Label::LOCAL);

	//void SetScaleYExcl(float y, ::Space const& space);
	//void SetScaleYExcl(float y, ::Space::Label space = ::Space::Label::LOCAL);

	//void SetScaleZ(float z, ::Space const& space);
	//void SetScaleZ(float z, ::Space::Label space = ::Space::Label::LOCAL);

	//void SetScaleZExcl(float z, ::Space const& space);
	//void SetScaleZExcl(float z, ::Space::Label space = ::Space::Label::LOCAL);

	//void Scale(glm::vec3 const& scale, ::Space const& space);
	//void Scale(float x, float y, float z, ::Space const& space);
	//void Scale(glm::vec3 const& scale, ::Space::Label space = ::Space::LOCAL);
	//void Scale(float x, float y, float z, ::Space::Label space = ::Space::LOCAL);

	//void ScaleExcl(glm::vec3 const& scale, ::Space const& space);
	//void ScaleExcl(float x, float y, float z, ::Space const& space);
	//void ScaleExcl(glm::vec3 const& scale, ::Space::Label space = ::Space::LOCAL);
	//void ScaleExcl(float x, float y, float z, ::Space::Label space = ::Space::LOCAL);

	//void ScaleX(float x, ::Space const& space);
	//void ScaleX(float x, ::Space::Label space = ::Space::LOCAL);

	//void ScaleXExcl(float x, ::Space const& space);
	//void ScaleXExcl(float x, ::Space::Label space = ::Space::LOCAL);

	//void ScaleY(float y, ::Space const& space);
	//void ScaleY(float y, ::Space::Label space = ::Space::LOCAL);

	//void ScaleYExcl(float y, ::Space const& space);
	//void ScaleYExcl(float y, ::Space::Label space = ::Space::LOCAL);

	//void ScaleZ(float z, ::Space const& space);
	//void ScaleZ(float z, ::Space::Label space = ::Space::LOCAL);

	//void ScaleZExcl(float z, ::Space const& space);
	//void ScaleZExcl(float z, ::Space::Label space = ::Space::LOCAL);

	// Space

	Space const& ObjectSpace() { UpdateSpace(); return mSpace; }
	Space const& LocalSpace();
	Space const& ParentSpace();

	glm::vec3 Local2World(glm::vec3 const& v);
	glm::vec3 Local2World(Detail::Axis const& axis);
	glm::vec3 World2Local(glm::vec3 const& v);
	glm::vec3 World2Local(Detail::Axis const& axis);
	glm::vec3 Space2Local(glm::vec3 const& v, Space const& src);
	glm::vec3 Space2Local(Detail::Axis const& axis, Space const& src);
	glm::vec3 Local2Space(glm::vec3 const& v, Space const& dest);
	glm::vec3 Local2Space(Detail::Axis const& axis, Space const& dest);
	glm::vec3 Local2Object(glm::vec3 const& v);
	glm::vec3 Local2Object(Detail::Axis const& axis);
	glm::vec3 Object2Local(glm::vec3 const& v);
	glm::vec3 Object2Local(Detail::Axis const& axis);
	glm::vec3 Space2Object(glm::vec3 const& v, Space const& src);
	glm::vec3 Space2Object(Detail::Axis const& axis, Space const& src);
	glm::vec3 Object2Space(glm::vec3 const& v, Space const& dest);
	glm::vec3 Object2Space(Detail::Axis const& axis, Space const& dest);
	glm::vec3 World2Object(glm::vec3 const& v);
	glm::vec3 World2Object(Detail::Axis const& axis);
	glm::vec3 Object2World(glm::vec3 const& v);
	glm::vec3 Object2World(Detail::Axis const& axis);

	inline glm::vec3 const& X() {
		return mX;
	}

	inline glm::vec3 const& Y() {
		return mY;
	}

	inline glm::vec3 const& Z() {
		return mZ;
	}

	void UpdateSpace();

	// Lookat

	void LookAt(glm::vec3 const& target);
	inline void LookAt(TransformComponent* transform) {
		LookAt(transform->Position());
	}
	inline void LookAt(GameObject* GO) {
		LookAt(GO->Retrieve<TransformComponent>()->Position());
	}

	// Parent-Child

	inline TransformComponent* Parent() {
		return mpParent;
	}

	bool HasParent() noexcept;

	inline std::vector<TransformComponent*> const& Children() {
		return mChildren;
	}

	inline std::size_t NumChildren() {
		return mChildren.size();
	}

	inline void AddChild(TransformComponent* transform) {
		TransformComponent* parent{ transform->mpParent };

		if (parent != nullptr) {
			parent->RemoveChild(transform);
		}

		glm::vec3 world_position{ transform->Position(Space::WORLD) };

		mChildren.push_back(transform);
		transform->mpParent = this;

		transform->mLocalPosition = mSpace.World2Space(world_position);
	}

	inline void AddChild(GameObject* GO) {
		AddChild(GO->Retrieve<TransformComponent>());
	}

	inline void RemoveChild(TransformComponent* transform) {
		auto it{ std::find(mChildren.begin(), mChildren.end(), transform) };
		if (it != mChildren.end()) {
			glm::vec3 world_position{ (*it)->Position(Space::WORLD) };

			(*it)->mpParent = nullptr;
			(*it)->SetPosition(world_position);

			mChildren.erase(it);
		}
	}
	inline void RemoveChild(GameObject* GO) {
		RemoveChild(GO->Retrieve<TransformComponent>());
	}

	// Model Matrix

	glm::mat4 ModelMatrix();

	glm::mat4 InverseModelMatrix();

private:
	virtual void InterfaceMain() override;

	glm::vec3 mWorldPosition;
	glm::vec3 mInterfaceWorldPosition;

	// This is the local position of the object _regardless_ of what its local
	// space actually happens to be.
	// (`mpParent == nullptr` means the local space is world space.)
	glm::vec3 mLocalPosition;
	glm::vec3 mLocalOrigin;

	// This is the Euler rotation of the object in radians and wrt a space
	// which has as its origin the object's position and as its axes the
	// world axes. No, this is also wrt to the object's local space.
	glm::vec3 mEulerRotation;

	// True if `mEulerRotation` reflects the current rotation of the object,
	// false if not.
	bool mEulerClean;

	// should be a normalized quaternion
	glm::quat mQuatRotation;

	// True if `mQuatClean` reflects the current rotation of the object,
	// false if not.
	bool mQuatClean;

	// This is the scale of the object in object space.
	glm::vec3 mScale;

	glm::vec3 mX;
	glm::vec3 mY;
	glm::vec3 mZ;
	
	Space mSpace;

	TransformComponent* mpParent;
	std::vector<TransformComponent*> mChildren;

	bool mLocalMatClean;
	glm::mat4 mModel;
};

#include "transform-component.ipp"
#endif