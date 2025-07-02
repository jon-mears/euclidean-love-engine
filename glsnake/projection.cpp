#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "app.hpp"
#include "projection.hpp"
#include "render-engine.hpp"

glm::mat4 Orthographic::ProjectionMatrix() {
	return glm::ortho(mLeft, mRight, mBottom, mTop);
}

Perspective::Perspective() {
	mAspect = (float)RenderEngine::Instance().WindowHeight() /
		(float)RenderEngine::Instance().WindowWidth();
}

glm::mat4 Perspective::ProjectionMatrix() {
	return glm::perspective(glm::radians(mFOVY), mAspect, mZNear, mZFar);
}

glm::mat4 NoProjection::ProjectionMatrix() {
	return glm::mat4{ 1 };
}