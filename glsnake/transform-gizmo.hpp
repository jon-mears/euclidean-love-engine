#ifndef TRANSFORM_GIZMO_HPP
#define TRANSFORM_GIZMO_HPP

#include <memory>

#include "component.hpp"
#include "line.hpp"
#include "point.hpp"

class GameObject;
class TransformComponent;

class TransformGizmo : public Component {
public:
	TransformGizmo(GameObject* GO);

	virtual void Start() override;
	virtual void Update() override;
	virtual void ConstUpdate() const override;

	virtual char const* Name() const override;

private:
	std::unique_ptr<Line<0, 0, 0, 1, 0, 0>> muX;
	std::unique_ptr<Line<0, 0, 0, 0, 1, 0>> muY;
	std::unique_ptr<Line<0, 0, 0, 0, 0, 1>> muZ;
	std::unique_ptr<Point> muO;

	TransformComponent *mpTransformC,
		*mpTransformX,
		*mpTransformY,
		*mpTransformZ,
		*mpTransformO;
};

//template <>
//struct Gizmo_Impl<TransformComponent> {
//	using type = TransformGizmo;
//};
#endif