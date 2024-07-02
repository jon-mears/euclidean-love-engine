#include "render_engine.hpp"
#include "resourcemanager.hpp"
#include "targeted_camera.hpp"
#include "gameobject.h"

#include "camera.h"

#include <iostream>
#include <string>
#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace {

#ifdef _glfw3_h_
	void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}
#endif
}

RenderEngine::RenderEngine() : mClearFlags(0), mWindowWidth(0), mWindowHeight(0), mpcWindowName(NULL) { }

void RenderEngine::draw() {
	clear_buffers();

	Camera* c = NULL;
	for (std::map<std::string, GameObject*>::iterator it = ResourceManager::instance().begin<GameObject>(); it != ResourceManager::instance().end<GameObject>(); ++it) {
		GameObject* go = it->second;

		if ((c = go->get_component<Camera>()) || (c = go->get_component<TargetedCamera>())) {
			c->draw();
		}
	}
}

void RenderEngine::clear_buffers() {
	GLbitfield clear_flags = 0;

	if (mClearFlags & Render::CLEAR_COLOR) {
		clear_flags |= GL_COLOR_BUFFER_BIT;
	}

	if (mClearFlags & Render::CLEAR_DEPTH) {
		clear_flags |= GL_DEPTH_BUFFER_BIT;
	}

	glClear(clear_flags);
}

/*
	void RenderEngine::register_drawer(System& sys) {
		drawers.push_back(sys.drawer); // priority queue?	

		drawer:
			void draw();
	}

	(utility of this is that this can associate each system to drawing in a particular window)
*/

void RenderEngine::startup() {
#ifdef _glfw3_h_
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mpWindow = glfwCreateWindow(mWindowWidth, mWindowHeight, mpcWindowName, NULL, NULL);

	if (mpWindow == NULL) {
		std::cout << "failed to initialize glfw" << std::endl;
		std::exit(-1);
	}

	glfwMakeContextCurrent(mpWindow);
	glfwSetFramebufferSizeCallback(mpWindow, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "failed to retrieve opengl funcs" << std::endl;
		std::exit(-1);
	}

#endif
}

RenderEngine& RenderEngine::instance() {
	static RenderEngine gRenderEngine;
	return gRenderEngine;
}