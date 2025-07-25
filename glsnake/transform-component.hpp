#ifndef TRANSFORM_COMPONENT_HPP
#define TRANSFORM_COMPONENT_HPP

#include <algorithm>
#include <vector>

#include "component.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GameObject;
class GLFWwindow;

class Space {
private:
	const glm::vec3& mrcBasis1, mrcBasis2, mrcBasis3;
	const glm::vec3& mrcOrigin;

public:

	inline const glm::vec3& X() { return mrcBasis1; }
	inline const glm::vec3& Y() { return mrcBasis2; }
	inline const glm::vec3& Z() { return mrcBasis3; }
	inline const glm::vec3& Origin() { return mrcOrigin; }

	Space(const glm::vec3& basis1, const glm::vec3& basis2, const glm::vec3& basis3,
		const glm::vec3& origin) : mrcBasis1{ basis1 }, mrcBasis2{ basis2 }, mrcBasis3{ basis3 },
		mrcOrigin{ origin } { }

	const glm::mat3& World2SpaceMatrix() {
		return glm::mat3{ mrcBasis1.x, mrcBasis2.x, mrcBasis3.x,
		mrcBasis1.y, mrcBasis2.y, mrcBasis3.y,
		mrcBasis1.z, mrcBasis2.z, mrcBasis3.z };
	}

	const glm::mat3& Space2WorldMatrix() {
		return glm::mat3{ mrcBasis1.x, mrcBasis1.y, mrcBasis1.z,
		mrcBasis2.x, mrcBasis2.y, mrcBasis2.z,
		mrcBasis3.x, mrcBasis3.y, mrcBasis3.z };
	}

	glm::vec3 World2Space(const glm::vec3& vrcVec) {
		return World2SpaceMatrix() * vrcVec;
	}

	glm::vec3 Space2World(const glm::vec3& vrcVec) {
		return Space2WorldMatrix() * vrcVec;
	}

	static Space* World() {
		static Space* spWorldSpace{ nullptr };

		if (spWorldSpace == nullptr) {
			static const glm::vec3 scWorldX{ 1.0f, 0.0f, 0.0f };
			static const glm::vec3 scWorldY{ 0.0f, 1.0f, 0.0f };
			static const glm::vec3 scWorldZ{ 0.0f, 0.0f, 1.0f };
			static const glm::vec3 scWorldOrigin{ 0.0f, 0.0f, 0.0f };

			spWorldSpace = new Space(scWorldX, scWorldY, scWorldZ, scWorldOrigin);
		}

		return spWorldSpace;
	}
};

class TransformComponent : public Component {
private:
	glm::vec3 mWorldPosition;
	glm::vec3 mInterfaceWorldPosition;

	glm::vec3 mLocalPosition;
	glm::vec3 mLocalOrigin{ 0 };

	glm::vec3 mEulerRotation;

	// should be a normalized quaternion
	glm::quat mQuatRotation;

	glm::vec3 mScale;

	glm::vec3 mLocalX = glm::vec3{ 1.0f, 0.0f, 0.0f };
	glm::vec3 mLocalY = glm::vec3{ 0.0f, 1.0f, 0.0f };
	glm::vec3 mLocalZ = glm::vec3{ 0.0f, 0.0f, 1.0f };

	Space* mpObjectSpace{ nullptr };

	TransformComponent* mpParent{ nullptr };
	std::vector<TransformComponent*> mChildren{};

	virtual void InterfaceMain() override;

// everything is ultimately given to these methods in world 
// coordinates, but of course the user may transform vectors 
// that are not originally in world coordinates to world 
// coordinates

public:
	TransformComponent(GameObject* pGO);
	void SetPosition(const glm::vec3& new_position, Space* pSpace = Space::World());
	void Translate(const glm::vec3& trans, Space* pSpace = Space::World());
	void SetEulerRotation(const glm::vec3& euler_rotation, Space* pSpace = nullptr);
	void SetQuaternionRotation(const glm::quat& quaternion_rotation);
	void EulerRotate(const glm::vec3& degs);
	void QuaternionRotate(const glm::quat& q);
	void RotateAboutAxis(const glm::vec3& axis, const float deg, 
		const glm::vec3& rcOrigin = Space::World()->Origin());
	void SetScale(const glm::vec3& new_scale);
	void Scale(const glm::vec3& rhs);

	//void AddChild(GameObject* pGO);
	//void AddChild(TransformComponent* pTransformC);

	//void RemoveChild(GameObject* pGO);
	//void RemoveChild(TransformComponent* pTransformC);

	//void SetParent(GameObject* pGO);
	//void SetParent(TransformComponent* pTransformC);

	void UpdateQuaternionRotation();
	void UpdateEulerRotation();
	void UpdateLocalAxes();

	//inline void RemoveParent() { mpParent->RemoveChild(this); mpParent = nullptr; }

	inline Space* GetSpace() { return mpObjectSpace; }

	void LookAt(const glm::vec3& target);

	inline void LookAt(TransformComponent* pTransform) {
		LookAt(pTransform->Position());
	}

	inline void LookAt(GameObject* pGO) {
		LookAt(pGO->Retrieve<TransformComponent>()->Position());
	}

	const glm::vec3 &Position() const;
	const glm::vec3 &EulerRotation() const;
	const glm::vec3& Scale() const;

	inline void SetParent(TransformComponent* pTransformC) {
		if (mpParent != nullptr) {
			mpParent->RemoveChild(this);
		}

		mpParent = pTransformC;
		pTransformC->mChildren.push_back(this);
	}

	inline void SetParent(GameObject* pGO) {
		SetParent(pGO->Retrieve<TransformComponent>());
	}

	inline void RemoveChild(TransformComponent* pTransformC) {
		auto it = std::find(mChildren.begin(), mChildren.end(), pTransformC);
		if (it != mChildren.end()) {
			(*it)->mpParent = nullptr;
			mChildren.erase(it);
		}
	}

	inline void RemoveChild(GameObject* pGO) {
		RemoveChild(pGO->Retrieve<TransformComponent>());
	}

	inline TransformComponent* Parent() {
		return mpParent;
	}

	inline const glm::vec3& LocalX() {
		return mLocalX;
	}

	inline std::size_t GetNumChildren() {
		return mChildren.size();
	}

	inline std::vector<TransformComponent*> const& GetChildren() {
		return mChildren;
	}

	inline void AddChild(TransformComponent* pTransformC) {
		auto pParent = pTransformC->mpParent;

		if (pParent != nullptr) {
			pParent->RemoveChild(pTransformC);
		}

		mChildren.push_back(pTransformC);
		pTransformC->mpParent = this;
	}

	inline void AddChild(GameObject* pGO) {
		AddChild(pGO->Retrieve<TransformComponent>());
	}

	inline const glm::vec3& LocalY() {
		return mLocalY;
	}

	inline const glm::vec3& LocalZ() {
		return mLocalZ;
	}

	glm::mat4 ModelMatrix();
	virtual void Start() override;
	virtual void Update() override;
	virtual void ConstUpdate() const override;

	inline const char* Name() const {
		return "Transform";
	}

};
#endif