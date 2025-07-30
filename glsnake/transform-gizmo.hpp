#ifndef TRANSFORM_GIZMO_HPP
#define TRANSFORM_GIZMO_HPP

#include "line.hpp"	
#include "transform-component.hpp"
#include "component.hpp"
#include "color.hpp"
#include "gizmo.hpp"

class Component;
class GameObject;

class TransformGizmo : public Component {
private:
	Line<0,0,0,1,0,0>* mX;
	Line<0,0,0,0,1,0>* mY;
	Line<0,0,0,0,0,1>* mZ;

	TransformComponent* mpTransformC, *mpTransformX, *mpTransformY,
		*mpTransformZ;
public:
	TransformGizmo(GameObject* pGO);

	virtual void Start() override;
	virtual void Update() override;
	virtual void ConstUpdate() const override;
	virtual const char* Name() const override;
};

//template <>
//struct Gizmo_Impl<TransformComponent> {
//	using type = TransformGizmo;
//};
#endif