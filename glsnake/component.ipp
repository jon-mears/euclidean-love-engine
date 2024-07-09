#ifndef COMPONENT_IPP
#define COMPONENT_IPP

#include "component.hpp"
#include "game-object.hpp"

template <typename C>
C* Component::GetComponent() {
	return mpGO->Retrieve<C>();
}

template <typename C>
const C* Component::GetComponent() const {
	return mpGO->Retrieve<C>();
}

#endif