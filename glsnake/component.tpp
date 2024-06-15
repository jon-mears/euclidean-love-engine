#ifndef COMPONENT_TPP
#define COMPONENT_TPP

#include "component.h"
#include "gameobject.h"

template <typename C>
C* Component::get_component() {
	return go->get_component<C>();
}
#endif