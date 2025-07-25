#ifndef GIZMO_HPP
#define GIZMO_HPP

class NoGizmo { };

template <typename C>
struct Gizmo_Impl {
	using type = NoGizmo;
};

template <typename C>
using Gizmo = typename Gizmo_Impl<C>::type;

#endif