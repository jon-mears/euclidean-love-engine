#ifndef TRANSFORM_GIZMO_HPP
#define TRANSFORM_GIZMO_HPP

#include "transform-component.hpp"
#include "component.hpp"
#include "gizmo.hpp"

class TransformGizmo : public Component {
private:

public:
	//void Start() override;
	//void Update() override;
};

template <>
struct Gizmo_Impl<TransformComponent> {
	using type = TransformGizmo;
};

#endif