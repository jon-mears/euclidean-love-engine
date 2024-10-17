#include "orthographic-component.hpp"
#include "game-object.hpp"
#include "projection-component.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

OrthographicComponent::OrthographicComponent(GameObject* pGO) : ProjectionComponent{ pGO }, mLeft{ -1 }, mRight{ 1 }, mBottom{ -1 }, mTop{ 1 } { }

glm::mat4 OrthographicComponent::ProjectionMatrix() {
	return glm::ortho(mLeft, mRight, mBottom, mTop);
}