#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "app.hpp"
#include "projection.hpp"
#include "render-engine.hpp"

Orthographic::Orthographic() {
	mLeft = 0;
	mRight = RenderEngine::Instance().WindowWidth();
	mBottom = RenderEngine::Instance().WindowHeight();
	mTop = 0;
}

glm::mat4 Orthographic::ProjectionMatrix() {
	double window_width = RenderEngine::Instance().WindowWidth();
	double window_height = RenderEngine::Instance().WindowHeight();

	double k = 1.0/std::max(window_width, window_height);

	//return glm::ortho(-(float)window_width, (float)window_width,
		//-(float)window_height, (float)window_height, mNear, mFar);
	return glm::ortho(-window_width*k, window_width*k, -window_height*k, window_height*k, -100.0, 100.0);
}

Perspective::Perspective() {
	mAspect = (float)RenderEngine::Instance().WindowWidth() /
		(float)RenderEngine::Instance().WindowHeight();
}

glm::mat4 Perspective::ProjectionMatrix() {
	int window_width = RenderEngine::Instance().WindowWidth();
	int window_height = RenderEngine::Instance().WindowHeight();
	return glm::perspective(glm::radians(mFOVY), (float)window_width/(float)window_height, mZNear, mZFar);
}

glm::mat4 NoProjection::ProjectionMatrix() {
	return glm::mat4{ 1 }; 
}

glm::mat4 AspectProjection::ProjectionMatrix() {
	double window_width = RenderEngine::Instance().WindowWidth();
	double window_height = RenderEngine::Instance().WindowHeight();

	double aspect_ratio = window_width / window_height;
	
	glm::mat4 proj_mat{ 1.0 };

	proj_mat = glm::scale(proj_mat, glm::vec3{ 1.0 / aspect_ratio, 1.0, 1.0 });
	return proj_mat;
}