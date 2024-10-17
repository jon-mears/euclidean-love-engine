#include "component.hpp"
#include "game-object.hpp"

Component::Component(GameObject* pGO) : mpGO(pGO) { }

void Component::Interface() { }