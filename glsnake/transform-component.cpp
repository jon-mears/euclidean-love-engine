#include "transform-component.hpp"
#include "game-object.hpp"
#include "component.hpp"
#include "imgui.h"
#include "resource-manager.hpp"

#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/quaternion.hpp>

#include <iostream>
#include "input-manager.hpp"
#include "math-3d.hpp"

TransformComponent::TransformComponent(GameObject* GO) :
	Component{ GO }, mWorldPosition{ 0 }, mInterfaceWorldPosition{ 0 },
	mLocalPosition{ 0 }, mLocalOrigin{ 0 }, mEulerRotation{ 0 },
	mEulerClean{ true }, mQuatRotation{ }, mQuatClean { true }, mScale{ 1 },
	mX{ 1.0f, 0.0f, 0.0f }, mY{ 0.0f, 1.0f, 0.0f }, mZ{ 0.0f, 0.0f, 1.0f },
	mSpace{ }, mpParent{ nullptr }, mChildren{ }, mLocalMatClean{ false },
	mModel{ 1 }
{ }

void TransformComponent::Start() { }

void TransformComponent::Update() {
	InputManager& im{ InputManager::Instance() };

	mLocalMatClean = false;
	mSpace.SetO(Position(Space::WORLD));
}

void TransformComponent::ConstUpdate() const { }

char const* TransformComponent::Name() const {
	return "Transform";
}

// Position

glm::vec3 TransformComponent::Position(Space const& space) {
	return Space2Space(mLocalPosition, space, LocalSpace());
}

glm::vec3 TransformComponent::Position(Space::Label label) {
	switch (label) {
	case Space::OBJECT:
		return glm::vec3{ 0 };
	case Space::LOCAL:
		return mLocalPosition;
	case Space::WORLD:
		return Local2World(mLocalPosition);
	case Space::OBJECT_WORLD:
		return glm::vec3{ 0 };
	default:
		throw "Space label not recognized.";
	}
}

void TransformComponent::SetPosition(
	glm::vec3 const& position, Space const& space
)
{
	mLocalPosition = Space2Local(position, space);
}

void TransformComponent::SetPosition(
	float x, float y, float z, Space const& space
)
{
	SetPosition(glm::vec3{ x, y, z }, space);
}

void TransformComponent::SetPositionExcl(
	glm::vec3 const& new_position, Space const& space
)
{
	SetPosition(new_position, space);
}

void TransformComponent::SetPositionExcl(
	float x, float y, float z, Space const& space
)
{
	SetPosition(x, y, z, space);
}

void TransformComponent::SetPosition(
	glm::vec3 const& new_position, Space::Label space
)
{
	switch (space) {
	case Space::OBJECT:
		mLocalPosition = Object2Local(new_position);

		break;
	case Space::LOCAL:
		mLocalPosition = new_position;

		break;
	case Space::WORLD:
		mLocalPosition = World2Local(new_position);

		break;
	default:
		
		throw "Space label not recognized.";
	}
}

void TransformComponent::SetPosition(
	float x, float y, float z, Space::Label space
)
{
	SetPosition(glm::vec3{ x, y, z }, space);
}

void TransformComponent::SetPositionExcl(
	glm::vec3 const& new_position, Space::Label space
)
{
	SetPosition(new_position, space);
}

void TransformComponent::SetPositionExcl(
	float x, float y, float z, Space::Label space
)
{
	SetPosition(x, y, z, space);
}

void TransformComponent::SetPositionX(float x, Space const& space) {
	glm::vec3 space_pos{ Local2Space(mLocalPosition, space) };

	space_pos.x = x;

	SetPosition(space_pos, space);
}

void TransformComponent::SetPositionX(float x, Space::Label space) {
	glm::vec3 space_pos;

	switch (space) {
	case Space::OBJECT:
		space_pos = Local2Object(mLocalPosition);
		space_pos.x = x;
		mLocalPosition = Object2Local(space_pos);

		break;
	case Space::LOCAL:
		mLocalPosition.x = x;

		break;
	case Space::WORLD:
		space_pos = Local2World(mLocalPosition);
		space_pos.x = x;
		mLocalPosition = World2Local(space_pos);

		break;
	default:
		throw "Space label not recognized.";
	}
}

void TransformComponent::SetPositionXExcl(float x, Space const& space) {
	SetPositionX(x, space);
}

void TransformComponent::SetPositionXExcl(float x, Space::Label space) {
	SetPositionX(x, space);
}

void TransformComponent::SetPositionY(float y, Space const& space) {
	glm::vec3 space_pos{ Local2Space(mLocalPosition, space) };

	space_pos.y = y;

	SetPosition(space_pos, space);
}

void TransformComponent::SetPositionY(float y, Space::Label space) {
	glm::vec3 space_pos;

	switch (space) {
	case Space::OBJECT:
		space_pos = Local2Object(mLocalPosition);
		space_pos.y = y;
		mLocalPosition = Object2Local(space_pos);

		break;
	case Space::LOCAL:
		mLocalPosition.y = y;

		break;
	case Space::WORLD:
		space_pos = Local2World(mLocalPosition);
		space_pos.y = y;
		mLocalPosition = World2Local(space_pos);

		break;
	default:
		throw "Space label not recognized.";
	}
}

void TransformComponent::SetPositionYExcl(float y, Space const& space) {
	SetPositionY(y, space);
}

void TransformComponent::SetPositionYExcl(float y, Space::Label space) {
	SetPositionY(y, space);
}

void TransformComponent::SetPositionZ(float z, Space const& space) {
	glm::vec3 space_pos{ Local2Space(mLocalPosition, space) };

	space_pos.z = z;

	SetPosition(space_pos, space);
}

void TransformComponent::SetPositionZ(float z, Space::Label space) {
	glm::vec3 space_pos;

	switch (space) {
	case Space::OBJECT:
		space_pos = Local2Object(mLocalPosition);
		space_pos.z = z;
		mLocalPosition = Object2Local(space_pos);

		break;
	case Space::LOCAL:
		mLocalPosition.z = z;

		break;
	case Space::WORLD:
		space_pos = Local2World(mLocalPosition);
		space_pos.z = z;
		mLocalPosition = World2Local(space_pos);

		break;
	default:
		throw "Space label not recognized.";
	}
}

void TransformComponent::SetPositionZExcl(float z, Space const& space) {
	SetPositionZ(z, space);
}

void TransformComponent::SetPositionZExcl(float z, Space::Label space) {
	SetPositionZ(z, space);
}

void TransformComponent::Translate(
	glm::vec3 const& trans, Space const& space
)
{
	glm::vec3 space_pos{ Local2Space(mLocalPosition, space) };

	space_pos += trans;

	mLocalPosition = Space2Local(space_pos, space);
}

void TransformComponent::Translate(
	float x, float y, float z, Space const& space
)
{
	Translate(glm::vec3{ x, y, z }, space);
}

void TransformComponent::Translate(
	glm::vec3 const& trans, Space::Label space
)
{
	glm::vec3 space_pos;

	switch (space) {
	case Space::OBJECT:
		space_pos = Local2Object(mLocalPosition);
		space_pos += trans;
		mLocalPosition = Object2Local(space_pos);

		break;
	case Space::LOCAL:
		mLocalPosition += trans;

		break;
	case Space::WORLD:
		space_pos = Local2World(mLocalPosition);
		space_pos += trans;
		mLocalPosition = World2Local(space_pos);

		break;
	default:
		throw "Space label not recognized.";
	}
}

void TransformComponent::Translate(
	float x, float y, float z, Space::Label space
)
{
	Translate(glm::vec3{ x, y, z }, space);
}

void TransformComponent::TranslateExcl(
	glm::vec3 const& trans, Space const& space
)
{
	Translate(trans, space);
}

void TransformComponent::TranslateExcl(
	float x, float y, float z, Space const& space
)
{
	Translate(x, y, z, space);
}

void TransformComponent::TranslateExcl(
	glm::vec3 const& trans, Space::Label space
)
{
	Translate(trans, space);
}

void TransformComponent::TranslateExcl(
	float x, float y, float z, Space::Label space
)
{
	Translate(x, y, z, space);
}

void TransformComponent::TranslateX(float x, Space const& space) {
	Translate(glm::vec3{ x, 0.0f, 0.0f }, space);
}

void TransformComponent::TranslateX(float x, Space::Label space) {
	Translate(glm::vec3{ x, 0.0f, 0.0f }, space);
}

void TransformComponent::TranslateXExcl(float x, Space const& space) {
	TranslateX(x, space);
}

void TransformComponent::TranslateXExcl(float x, Space::Label space) {
	TranslateX(x, space);
}

void TransformComponent::TranslateY(float y, Space const& space) {
	Translate(glm::vec3{ 0.0f, y, 0.0f }, space);
}

void TransformComponent::TranslateY(float y, Space::Label space) {
	Translate(glm::vec3{ 0.0f, y, 0.0f }, space);
}

void TransformComponent::TranslateYExcl(float y, Space const& space) {
	TranslateY(y, space);
}

void TransformComponent::TranslateYExcl(float y, Space::Label space) {
	TranslateY(y, space);
}

void TransformComponent::TranslateZ(float z, Space const& space) {
	Translate(glm::vec3{ 0.0f, 0.0f, z }, space);
}

void TransformComponent::TranslateZ(float z, Space::Label space) {
	Translate(glm::vec3{ 0.0f, 0.0f, z }, space);
}

void TransformComponent::TranslateZExcl(float z, Space const& space) {
	TranslateZ(z, space);
}

void TransformComponent::TranslateZExcl(float z, Space::Label space) {
	TranslateZ(z, space);
}

// Euler Rotation

glm::vec3 TransformComponent::EulerRotation(Space const& space) {
	MakeEulerClean();
	return World2Space(Axis(mEulerRotation), space);
}

glm::vec3 TransformComponent::EulerRotation(Space::Label space) {
	MakeEulerClean();
	
	switch (space) {
	case Space::OBJECT:
		return Local2Object(Axis(mEulerRotation));
	case Space::LOCAL:
		return mEulerRotation;
	case Space::WORLD:
		return Local2World(Axis(mEulerRotation));
	default:
		throw "Space label not recognized.";
	}
}

void TransformComponent::SetEulerRotation(
	Degrees x, Degrees y, Degrees z, Space const& space
)
{
	SetEulerRotation(Deg2Rad(x), Deg2Rad(y), Deg2Rad(z), space);
}

void TransformComponent::SetEulerRotation(
	Degrees x, Degrees y, Degrees z, Space::Label space
)
{
	SetEulerRotation(Deg2Rad(x), Deg2Rad(y), Deg2Rad(z), space);
}

void TransformComponent::SetEulerRotation(
	Radians x, Radians y, Radians z, Space const& space
)
{
	mEulerRotation = Space2Local(Axis(glm::vec3{ x, y, z }), space);

	mEulerClean = true;
	mQuatClean = false;
}

void TransformComponent::SetEulerRotation(
	Radians x, Radians y, Radians z, Space::Label space
)
{
	switch (space) {
	case Space::OBJECT:
		mEulerRotation = Object2Local(Axis(glm::vec3{ x, y, z }));

		break;
	case Space::LOCAL:
		mEulerRotation = Local2World(Axis(glm::vec3{ x, y, z }));

		break;
	case Space::OBJECT_WORLD:
		mEulerRotation = glm::vec3{ x, y, z };

		break;
	default:
		throw "Space label not recognized.";
	}

	mEulerClean = true;
	mQuatClean = false;
}

void TransformComponent::SetEulerRotationExcl(
	Radians x, Radians y, Radians z, Space const& space
)
{
	SetEulerRotation(x, y, z, space);
}

void TransformComponent::SetEulerRotationExcl(
	Degrees x, Degrees y, Degrees z, Space const& space
)
{
	SetEulerRotationExcl(Deg2Rad(x), Deg2Rad(y), Deg2Rad(z), space);
}

void TransformComponent::SetEulerRotationExcl(
	Radians x, Radians y, Radians z,
	Space::Label space
)
{
	SetEulerRotation(x, y, z, space);
}

void TransformComponent::SetEulerRotationExcl(
	Degrees x, Degrees y, Degrees z,
	Space::Label space
)
{
	SetEulerRotationExcl(Deg2Rad(x), Deg2Rad(y), Deg2Rad(z), space);
}

void TransformComponent::SetEulerRotationX(Radians x, Space const& space) {
	MakeEulerClean();

	glm::vec3 space_euler{ World2Space(Axis(mEulerRotation), space) };

	space_euler.x = x;

	mEulerRotation = Space2World(Axis(mEulerRotation), space);

	mQuatClean = false;
}

void TransformComponent::SetEulerRotationX(Degrees x, Space const& space) {
	SetEulerRotationX(Deg2Rad(x), space);
}

void TransformComponent::SetEulerRotationX(
	Radians x, Space::Label space
)
{
	MakeEulerClean();

	glm::vec3 space_euler;

	switch (space) {
	case Space::OBJECT:
		space_euler = World2Object(Axis(mEulerRotation));
		space_euler.x = x;
		mEulerRotation = Object2World(Axis(space_euler));

		break;
	case Space::LOCAL:
		space_euler = World2Local(Axis(mEulerRotation));
		space_euler.x = x;
		mEulerRotation = Local2World(Axis(space_euler));

		break;
	case Space::WORLD:
		mEulerRotation.x = x;
	}

	mQuatClean = false;
}

void TransformComponent::SetEulerRotationX(
	Degrees x, Space::Label space
)
{
	SetEulerRotationX(Deg2Rad(x), space);
}

void TransformComponent::SetEulerRotationXExcl(Radians x, Space const& space) {
	SetEulerRotationX(x, space);
}

void TransformComponent::SetEulerRotationXExcl(Degrees x, Space const& space) {
	SetEulerRotationX(x, space);
}

void TransformComponent::SetEulerRotationXExcl(Radians x, Space::Label space) {
	SetEulerRotationXExcl(x, space);
}

void TransformComponent::SetEulerRotationXExcl(Degrees x, Space::Label space) {
	SetEulerRotationXExcl(x, space);
}

//

void TransformComponent::SetEulerRotationY(Radians y, Space const& space) {
	MakeEulerClean();

	glm::vec3 space_euler{ World2Space(Axis(mEulerRotation), space) };

	space_euler.y = y;

	mEulerRotation = Space2World(Axis(mEulerRotation), space);

	mQuatClean = false;
}

void TransformComponent::SetEulerRotationY(Degrees y, Space const& space) {
	SetEulerRotationY(Deg2Rad(y), space);
}

void TransformComponent::SetEulerRotationY(
	Radians y, Space::Label space
)
{
	MakeEulerClean();

	glm::vec3 space_euler;

	switch (space) {
	case Space::OBJECT:
		space_euler = World2Object(Axis(mEulerRotation));
		space_euler.y = y;
		mEulerRotation = Object2World(Axis(space_euler));

		break;
	case Space::LOCAL:
		space_euler = World2Local(Axis(mEulerRotation));
		space_euler.y = y;
		mEulerRotation = Local2World(Axis(space_euler));

		break;
	case Space::WORLD:
		mEulerRotation.y = y;
	}

	mQuatClean = false;
}

void TransformComponent::SetEulerRotationY(
	Degrees y, Space::Label space
)
{
	SetEulerRotationY(Deg2Rad(y), space);
}

void TransformComponent::SetEulerRotationYExcl(Radians y, Space const& space) {
	SetEulerRotationY(y, space);
}

void TransformComponent::SetEulerRotationYExcl(Degrees y, Space const& space) {
	SetEulerRotationY(y, space);
}

void TransformComponent::SetEulerRotationYExcl(Radians y, Space::Label space) {
	SetEulerRotationYExcl(y, space);
}

void TransformComponent::SetEulerRotationYExcl(Degrees y, Space::Label space) {
	SetEulerRotationYExcl(y, space);
}

//

void TransformComponent::SetEulerRotationZ(Radians z, Space const& space) {
	MakeEulerClean();

	glm::vec3 space_euler = World2Space(Axis(mEulerRotation), space);

	space_euler.z = z;

	mEulerRotation = Space2World(Axis(mEulerRotation), space);

	mQuatClean = false;
}

void TransformComponent::SetEulerRotationZ(Degrees z, Space const& space) {
	SetEulerRotationZ(Deg2Rad(z), space);
}

void TransformComponent::SetEulerRotationZ(
	Radians z, Space::Label space
)
{
	MakeEulerClean();

	glm::vec3 space_euler;

	switch (space) {
	case Space::OBJECT:
		space_euler = World2Object(Axis(mEulerRotation));
		space_euler.z = z;
		mEulerRotation = Object2World(Axis(space_euler));

		break;
	case Space::LOCAL:
		space_euler = World2Local(Axis(mEulerRotation));
		space_euler.z = z;
		mEulerRotation = Local2World(Axis(space_euler));

		break;
	case Space::WORLD:
		mEulerRotation.z = z;
	}

	mQuatClean = false;
}

void TransformComponent::SetEulerRotationZ(
	Degrees z, Space::Label space
)
{
	SetEulerRotationZ(Deg2Rad(z), space);
}

void TransformComponent::SetEulerRotationZExcl(Radians z, Space const& space) {
	SetEulerRotationZ(z, space);
}

void TransformComponent::SetEulerRotationZExcl(Degrees z, Space const& space) {
	SetEulerRotationZ(z, space);
}

void TransformComponent::SetEulerRotationZExcl(Radians z, Space::Label space) {
	SetEulerRotationZExcl(z, space);
}

void TransformComponent::SetEulerRotationZExcl(Degrees z, Space::Label space) {
	SetEulerRotationZExcl(z, space);
}

void TransformComponent::EulerRotate(
	Radians x, Radians y, Radians z, Space const& space
)
{
	MakeEulerClean();

	glm::vec3 space_euler{ World2Space(Axis(mEulerRotation), space) };

	space_euler += glm::vec3{ x, y, z };

	mEulerRotation = Space2World(Axis(space_euler), space);

	mQuatClean = false;
}

void TransformComponent::EulerRotate(
	Degrees x, Degrees y, Degrees z, Space const& space
)
{
	EulerRotate(Deg2Rad(x), Deg2Rad(y), Deg2Rad(z), space);
}

void TransformComponent::EulerRotate(
	Radians x, Radians y, Radians z, Space::Label space
)
{
	MakeEulerClean();

	glm::vec3 euler_space;

	switch (space) {
	case Space::Label::OBJECT:
		euler_space = World2Object(Axis(mEulerRotation));
		euler_space += glm::vec3{ x, y, z };
		mEulerRotation = Object2World(Axis(euler_space));

		break;
	case Space::Label::LOCAL:
		euler_space = World2Local(Axis(mEulerRotation));
		euler_space += glm::vec3{ x, y, z };
		mEulerRotation = Local2World(Axis(euler_space));

		break;
	case Space::Label::WORLD:
		mEulerRotation += glm::vec3{ x, y, z };
		
		break;
	default:
		throw "Space label not recognized.";
	}

	mQuatClean = false;
}

void TransformComponent::EulerRotate(
	Degrees x, Degrees y, Degrees z, Space::Label space
)
{
	EulerRotate(Deg2Rad(x), Deg2Rad(y), Deg2Rad(z), space);
}

void TransformComponent::EulerRotateExcl(
	Radians x, Radians y, Radians z, Space const& space
)
{
	EulerRotate(x, y, z, space);
}

void TransformComponent::EulerRotateExcl(
	Degrees x, Degrees y, Degrees z, Space const& space
)
{
	EulerRotate(x, y, z, space);
}

void TransformComponent::EulerRotateExcl(
	Radians x, Radians y, Radians z, Space::Label space
)
{
	EulerRotate(x, y, z, space);
}

void TransformComponent::EulerRotateExcl(
	Degrees x, Degrees y, Degrees z, Space::Label space
)
{
	EulerRotate(x, y, z, space);
}

void TransformComponent::EulerRotateX(Radians x, Space const& space) {
	MakeEulerClean();
	
	glm::vec3 euler_space{ World2Space(Axis(mEulerRotation), space) };

	euler_space.x += x;

	mEulerRotation = Space2World(Axis(euler_space), space);

	mQuatClean = false;
}

void TransformComponent::EulerRotateX(Degrees x, Space const& space) {
	EulerRotateX(Deg2Rad(x), space);
}

void TransformComponent::EulerRotateX(Radians x, Space::Label space) {
	MakeEulerClean();
	
	glm::vec3 euler_space;
	
	switch (space) {
	case Space::Label::OBJECT:
		euler_space = World2Object(Axis(mEulerRotation));
		euler_space.x += x;

		mEulerRotation = Object2World(Axis(euler_space));

		break;
	case Space::Label::LOCAL:
		euler_space = World2Local(Axis(mEulerRotation));
		euler_space.x += x;

		mEulerRotation = Local2World(Axis(euler_space));

		break;
	case Space::Label::WORLD:
		mEulerRotation.x += x;
	}

	mQuatClean = false;
}

void TransformComponent::EulerRotateX(Degrees x, Space::Label space) {
	EulerRotateX(Deg2Rad(x), space);
}

void TransformComponent::EulerRotateXExcl(Radians x, Space const& space) {
	EulerRotateX(x, space);
}

void TransformComponent::EulerRotateXExcl(Degrees x, Space const& space) {
	EulerRotateX(x, space);
}

void TransformComponent::EulerRotateXExcl(Radians x, Space::Label space) {
	EulerRotateX(x, space);
}

void TransformComponent::EulerRotateXExcl(Degrees x, Space::Label space) {
	EulerRotateX(x, space);
}

//

void TransformComponent::EulerRotateY(Radians y, Space const& space) {
	MakeEulerClean();

	glm::vec3 euler_space{ World2Space(Axis(mEulerRotation), space) };

	euler_space.y += y;

	mEulerRotation = Space2World(Axis(euler_space), space);

	mQuatClean = false;
}

void TransformComponent::EulerRotateY(Degrees y, Space const& space) {
	EulerRotateY(Deg2Rad(y), space);
}

void TransformComponent::EulerRotateY(Radians y, Space::Label space) {
	MakeEulerClean();

	glm::vec3 euler_space;

	switch (space) {
	case Space::Label::OBJECT:
		euler_space = World2Object(Axis(mEulerRotation));
		euler_space.y += y;

		mEulerRotation = Object2World(Axis(euler_space));

		break;
	case Space::Label::LOCAL:
		euler_space = World2Local(Axis(mEulerRotation));
		euler_space.y += y;

		mEulerRotation = Local2World(Axis(euler_space));

		break;
	case Space::Label::WORLD:
		mEulerRotation.y += y;
	}

	mQuatClean = false;
}

void TransformComponent::EulerRotateY(Degrees y, Space::Label space) {
	EulerRotateY(Deg2Rad(y), space);
}

void TransformComponent::EulerRotateYExcl(Radians y, Space const& space) {
	EulerRotateY(y, space);
}

void TransformComponent::EulerRotateYExcl(Degrees y, Space const& space) {
	EulerRotateY(y, space);
}

void TransformComponent::EulerRotateYExcl(Radians y, Space::Label space) {
	EulerRotateY(y, space);
}

void TransformComponent::EulerRotateYExcl(Degrees y, Space::Label space) {
	EulerRotateY(y, space);
}

//

void TransformComponent::EulerRotateZ(Radians z, Space const& space) {
	MakeEulerClean();

	glm::vec3 euler_space{ World2Space(Axis(mEulerRotation), space) };

	euler_space.z += z;

	mEulerRotation = Space2World(Axis(euler_space), space);

	mQuatClean = false;
}

void TransformComponent::EulerRotateZ(Degrees z, Space const& space) {
	EulerRotateZ(Deg2Rad(z), space);
}

void TransformComponent::EulerRotateZ(Radians z, Space::Label space) {
	MakeEulerClean();

	glm::vec3 euler_space;

	switch (space) {
	case Space::Label::OBJECT:
		euler_space = World2Object(Axis(mEulerRotation));
		euler_space.z += z;

		mEulerRotation = Object2World(Axis(euler_space));

		break;
	case Space::Label::LOCAL:
		euler_space = World2Local(Axis(mEulerRotation));
		euler_space.z += z;

		mEulerRotation = Local2World(Axis(euler_space));

		break;
	case Space::Label::WORLD:
		mEulerRotation.z += z;
	}

	mQuatClean = false;
}

void TransformComponent::EulerRotateZ(Degrees z, Space::Label space) {
	EulerRotateZ(Deg2Rad(z), space);
}

void TransformComponent::EulerRotateZExcl(Radians z, Space const& space) {
	EulerRotateZ(z, space);
}

void TransformComponent::EulerRotateZExcl(Degrees z, Space const& space) {
	EulerRotateZ(z, space);
}

void TransformComponent::EulerRotateZExcl(Radians z, Space::Label space) {
	EulerRotateZ(z, space);
}

void TransformComponent::EulerRotateZExcl(Degrees z, Space::Label space) {
	EulerRotateZ(z, space);
}

void TransformComponent::MakeEulerClean() {
	if (!mEulerClean) UpdateEuler();
}

void TransformComponent::UpdateEuler() {
	mEulerRotation = glm::eulerAngles(mQuatRotation);

	mEulerClean = true;
}

// Quat Rotation

glm::quat TransformComponent::QuatRotation() noexcept {
	MakeQuatClean();
	return mQuatRotation;
}

void TransformComponent::QuatRotate(glm::quat const& q) {
	if (!mQuatClean) MakeQuatClean();

	mQuatRotation = q * mQuatRotation;

	mEulerClean = false;
}

void TransformComponent::MakeQuatClean() {
	if (!mQuatClean) UpdateQuat();
}

void TransformComponent::UpdateQuat() {
	glm::mat4 vMatrix{ 1 };

	vMatrix = glm::rotate(vMatrix, mEulerRotation.y, glm::vec3{ 0.0f, 1.0f,
		0.0f });
	vMatrix = glm::rotate(vMatrix, mEulerRotation.x, glm::vec3{ 1.0f, 0.0f,
		0.0f });
	vMatrix = glm::rotate(vMatrix, mEulerRotation.z, glm::vec3{ 0.0f, 0.0f,
		1.0f });

	mQuatRotation.w = 0.5 * std::sqrt(std::max(0.0f,
		1 + vMatrix[0][0] + vMatrix[1][1] + vMatrix[2][2]));
	mQuatRotation.x = 0.5 * std::sqrt(std::max(0.0f,
		1 + vMatrix[0][0] - vMatrix[1][1] - vMatrix[2][2]));
	mQuatRotation.y = 0.5 * std::sqrt(std::max(0.0f,
		1 - vMatrix[0][0] + vMatrix[1][1] - vMatrix[2][2]));
	mQuatRotation.z = 0.5 * std::sqrt(std::max(0.0f,
		1 - vMatrix[0][0] - vMatrix[1][1] + vMatrix[2][2]));

	mQuatRotation.x = std::copysign(mQuatRotation.x, vMatrix[2][1] -
		vMatrix[1][2]);
	mQuatRotation.y = std::copysign(mQuatRotation.y, vMatrix[0][2] -
		vMatrix[2][0]);
	mQuatRotation.z = std::copysign(mQuatRotation.z, vMatrix[1][0] -
		vMatrix[0][1]);

	mQuatClean = true;
}

glm::vec3 TransformComponent::Local2World(glm::vec3 const& v) {
	if (!HasParent()) return v;
	else return Space2World(v, ParentSpace());
}

glm::vec3 TransformComponent::Local2World(Detail::Axis const& axis) {
	if (!HasParent()) return axis.ref;
	else return Space2World(axis, ParentSpace());
}

glm::vec3 TransformComponent::World2Local(glm::vec3 const& v) {
	if (!HasParent()) return v;
	else return World2Space(v, ParentSpace());
}

glm::vec3 TransformComponent::World2Local(Detail::Axis const& axis) {
	if (!HasParent()) return axis.ref;
	else return World2Space(axis, ParentSpace());
}

glm::vec3 TransformComponent::Space2Local(
	glm::vec3 const& v, Space const& src
)
{
	if (!HasParent()) return Space2World(v, src);
	else return Space2Space(v, ParentSpace(), src);
}

glm::vec3 TransformComponent::Space2Local(
	Detail::Axis const& axis, Space const& src
)
{
	if (!HasParent()) return Space2World(axis, src);
	else return Space2Space(axis, ParentSpace(), src);
}

glm::vec3 TransformComponent::Local2Space(
	glm::vec3 const& v, Space const& dest
)
{
	if (!HasParent()) return World2Space(v, dest);
	else return Space2Space(v, dest, ParentSpace());
}

glm::vec3 TransformComponent::Local2Space(
	Detail::Axis const& axis, Space const& dest
)
{
	if (!HasParent()) return World2Space(axis, dest);
	else return Space2Space(axis, dest, ParentSpace());
}

glm::vec3 TransformComponent::Local2Object(glm::vec3 const& v) {
	if (!HasParent()) return World2Space(v, ObjectSpace());
	else return Space2Space(v, ObjectSpace(), ParentSpace());
}

glm::vec3 TransformComponent::Local2Object(Detail::Axis const& axis) {
	if (!HasParent()) return World2Space(axis, ObjectSpace());
	else return Space2Space(axis, ObjectSpace(), ParentSpace());
}

glm::vec3 TransformComponent::Object2Local(glm::vec3 const& v) {
	if (!HasParent()) return Space2World(v, ObjectSpace());
	else return Space2Space(v, ParentSpace(), ObjectSpace());
}

glm::vec3 TransformComponent::Object2Local(Detail::Axis const& axis) {
	if (!HasParent()) return Space2World(axis, ObjectSpace());
	else return Space2Space(axis, ParentSpace(), ObjectSpace());
}

glm::vec3 TransformComponent::Space2Object(
	glm::vec3 const& v, Space const& src
)
{
	return Space2Space(v, ObjectSpace(), src);
}

glm::vec3 TransformComponent::Space2Object(
	Detail::Axis const& axis, Space const& src
)
{
	return Space2Space(axis, ObjectSpace(), src);
}

glm::vec3 TransformComponent::Object2Space(
	glm::vec3 const& v, Space const& dest
)
{
	return Space2Space(v, dest, ObjectSpace());
}

glm::vec3 TransformComponent::Object2Space(
	Detail::Axis const& axis, Space const& dest
)
{
	return Space2Space(axis, dest, ObjectSpace());
}

glm::vec3 TransformComponent::World2Object(glm::vec3 const& v) {
	return World2Space(v, ObjectSpace());
}

glm::vec3 TransformComponent::World2Object(Detail::Axis const& axis) {
	return World2Space(axis, ObjectSpace());
}

glm::vec3 TransformComponent::Object2World(glm::vec3 const& v) {
	return Space2World(v, ObjectSpace());
}

glm::vec3 TransformComponent::Object2World(Detail::Axis const& axis) {
	return Space2World(axis, ObjectSpace());
}

Space const& TransformComponent::ParentSpace() {
	try {
		return mpParent->ObjectSpace();
	}
	catch (...) {
		return Space::World();
	}
}

Space const& TransformComponent::LocalSpace() {
	if (HasParent()) return mpParent->ObjectSpace();
	else return Space::World();
}

void TransformComponent::InterfaceMain() {

	enum RotationT {
		QUAT,
		EULER,
		ANGLE_AXIS
	};

	const char* options[] = {
		"Euler Angles",
		"Quaternion",
		"Angle Axis"
	};

	static int selection = 0;

	static Space::Label position_space = Space::LOCAL;
	static Space::Label rotation_space = Space::OBJECT_WORLD;
	static Space::Label scale_space = Space::OBJECT;

	glm::vec3 local_position = Position(position_space);
	glm::vec3 euler_rotation = EulerRotation();
	glm::vec3 scale = mScale;

	ImGui::Text("Position:");

	ImGui::Indent();

	if (ImGui::RadioButton("World", position_space == Space::WORLD)) position_space = Space::WORLD;

	ImGui::SameLine();

	if (ImGui::RadioButton("Local", position_space == Space::LOCAL)) position_space = Space::LOCAL;

	ImGui::SameLine();

	if (ImGui::RadioButton("Object", position_space == Space::OBJECT)) position_space = Space::OBJECT;

	if (ImGui::DragFloat3("##Position", glm::value_ptr(local_position))) {
		SetPosition(local_position, position_space);
	}

	ImGui::Unindent();

	ImGui::Text("Rotation:");

	ImGui::Indent();

	if (ImGui::BeginCombo("Format", options[selection])) {
		for (int i = 0; i < IM_ARRAYSIZE(options); ++i) {
			const bool is_selected = i == selection;
			if (ImGui::Selectable(options[i], is_selected)) {
				selection = i;
			}
		}

		ImGui::EndCombo();
	}

	if (ImGui::DragFloat3("##Rotation", glm::value_ptr(euler_rotation))) {
		SetEulerRotation(Rad(euler_rotation.x),Rad(euler_rotation.y),
			Rad(euler_rotation.z));
	}

	ImGui::Unindent();

	ImGui::Text("Scale:");

	ImGui::Indent();

	ImGui::DragFloat3("##Scale", glm::value_ptr(mScale));

	ImGui::Unindent();
}

//void TransformComponent::Translate(const glm::vec3& translation, Space* pSpace) {
//	glm::vec3 transl = translation.x * pSpace->X() + translation.y *
//		pSpace->Y() + translation.z * pSpace->Z();
//
//	mLocalPosition += transl;
//
//	//for (auto child : mChildren) {
//	//	child->Translate(transl);
//	//}
//}
//
//void TransformComponent::SetEulerRotation(const glm::vec3& euler_rotation, 
//	Space* pSpace) {
//	if (pSpace == nullptr) { pSpace = ObjectSpace(); }
//
//	mEulerRotation = euler_rotation.x * pSpace->X() + euler_rotation.y * pSpace->Y() +
//		euler_rotation.z * pSpace->Z();
//
//	mQuatClean = false;
//}
//
//void TransformComponent::EulerRotate(const glm::vec3& rotation) {
//	if (!mEulerClean) UpdateEulerRotation();
//
//	mEulerRotation += rotation;
//	mQuatClean = false;
//}
	
// axis should be normalized
//void TransformComponent::RotateAboutAxis(const glm::vec3& axis, const float deg,
//	const glm::vec3& rcOrigin) {
//	const float rad = glm::radians(deg) / 2;
//	const glm::quat quaternion = glm::quat(glm::cos(rad), glm::sin(rad) * axis);
//
//	mQuatRotation = quaternion * mQuatRotation;
//
//	const glm::mat3 vcRotationMatrix(quaternion);
//
//	const glm::vec3 vcX = vcRotationMatrix * glm::vec3{ 1.0f, 0.0f, 0.0f };
//	const glm::vec3 vcY = vcRotationMatrix * glm::vec3{ 0.0f, 1.0f, 0.0f };
//	const glm::vec3 vcZ = vcRotationMatrix * glm::vec3{ 0.0f, 0.0f, 1.0f };
//	Space* vpSpace = new Space(vcX, vcY, vcZ, rcOrigin);
//	SetPosition(mWorldPosition, vpSpace);
//}

void TransformComponent::SetScale(glm::vec3 const& scale,
	Space::Label eSpace) {
	//ResourceManager& rm = ResourceManager::Instance();

	switch (eSpace) {
	case Space::OBJECT:
		mScale = scale;
		break;
	default:
		throw "Space label not recognized.";
	//case Space::LOCAL:
	//	//GameObject* parent = rm.New<GameObject>();
	//	parent->Retrieve<TransformComponent>()->AddChild(this);
	//	break;
	}
}

//void TransformComponent::Scale(const glm::vec3& scale) {
//	mScale += scale;
//}

glm::vec3 TransformComponent::Scale(Space::Label eSpace) {
	switch (eSpace) {
	case Space::Label::OBJECT:
		return mScale;
	default:
		throw "Space label not recognized.";
	}
}

void TransformComponent::SetQuatRotation(glm::quat const& quat_rotation) {
	mQuatRotation = quat_rotation;

	mEulerClean = false;
}

glm::mat4 TransformComponent::ModelMatrix() {
	if (mLocalMatClean) {
		return mModel;
	}

	else {
		mModel = glm::mat4{ 1 };
		mModel = glm::translate(mModel, mLocalPosition);

		if (mQuatClean) {
			mModel = mModel * glm::toMat4(mQuatRotation);
		}
		else {
			glm::vec3 euler_rotation = EulerRotation();

			mModel = glm::rotate(mModel, glm::radians(euler_rotation.y),
				glm::vec3(0, 1, 0));
			mModel = glm::rotate(mModel, glm::radians(euler_rotation.x),
				glm::vec3(1, 0, 0));
			mModel = glm::rotate(mModel, glm::radians(euler_rotation.z),
				glm::vec3(0, 0, 1));
		}

		mModel = glm::scale(mModel, mScale);

		if (mpParent) {
			mModel = mpParent->ModelMatrix() * mModel;
		}

		mLocalMatClean = true;
		return mModel;
	}
}

// this can (probably) be a LOT more efficient using the logical inverses of the simple
// transformations
glm::mat4 TransformComponent::InverseModelMatrix() {
	return glm::inverse(ModelMatrix());
}

bool TransformComponent::HasParent() noexcept {
	return mpParent != nullptr;
}

void TransformComponent::LookAt(const glm::vec3& crTarget) {
	glm::vec3 dir = glm::normalize(mLocalPosition - crTarget);
	glm::vec3 right = glm::cross(dir, glm::vec3{ 0.0f, 1.0f, 0.0f });
	glm::vec3 up = glm::cross(dir, right);

	/*
		[right.x   up.x   dir.x   0   ]
		[right.y   up.y   dir.y   0   ]
		[right.z   up.z   dir.z   0   ]
		[0         0      0       1   ]
	*/

	mQuatRotation = Math3D::Quaternion(right.x, up.x, dir.x, right.y, up.y, dir.y, right.z, up.z, dir.z);
	UpdateEuler();
}

void TransformComponent::UpdateSpace() {
	MakeQuatClean();

	glm::mat3 rotation_mat{ glm::toMat3(mQuatRotation) };
	
	mZ = glm::normalize(rotation_mat * glm::vec3(0, 0, 1));
	mX = glm::normalize(rotation_mat * glm::vec3(1, 0, 0));
	mY = glm::normalize(glm::cross(mZ, mX));

	mSpace.SetO(Position(Space::WORLD));

	mSpace.SetX(mX);
	mSpace.SetY(mY);
	mSpace.SetZ(mZ);
}