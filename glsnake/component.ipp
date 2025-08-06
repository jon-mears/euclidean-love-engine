#ifndef COMPONENT_IPP
#define COMPONENT_IPP

#include "component.hpp"

#include "game-object.hpp"

template <typename C>
C* Component::Get() {
	return mpGO->Retrieve<C>();
}

template <typename C>
C const* Component::Get() const {
	return mpGO->Retrieve<C>();
}
#endif