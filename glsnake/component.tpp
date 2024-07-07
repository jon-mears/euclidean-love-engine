#ifndef COMPONENT_TPP
#define COMPONENT_TPP

#include "component.h"
#include "gameobject.h"

template <typename C>
C* Component::GetComponent() {
	return go->get_component<C>();
}

template <typename C>
const C* Component::GetComponent() const {
	return go->get_component<C>();
}

#endif