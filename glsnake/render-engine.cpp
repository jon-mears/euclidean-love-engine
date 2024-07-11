#include "render-engine.hpp"
#include "resource-manager.hpp"
#include "targeted-camera-component.hpp"
#include "game-object.hpp"

#include "camera-component.hpp"

#include <iostream>
#include <string>
#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace FramebufferCallback {
#ifdef _glfw3_h_
	void FramebufferSizeCallback(GLFWwindow* window, int width, int height) {
		//RenderEngine::Instance().SetWindowWidth(width);
		//RenderEngine::Instance().SetWindowHeight(height);
		glViewport(0, 0, width, height);
	}
#endif
}

RenderEngine::RenderEngine() : mfClearFlags{ 0 }, mWindowWidth{ 0 }, mWindowHeight{ 0 }, mpcWindowName{ nullptr } { }

void RenderEngine::Draw() {
	ClearBuffers();

	CameraComponent* pCamera = nullptr;
	for (std::map<std::string, GameObject*>::iterator it = ResourceManager::Instance().Begin<GameObject>(); it != ResourceManager::Instance().End<GameObject>(); ++it) {
		GameObject* pGO = it->second;

		if ((pCamera = pGO->Retrieve<CameraComponent>()) || (pCamera = pGO->Retrieve<TargetedCameraComponent>())) {
			pCamera->Draw();
		}
	}
}

void RenderEngine::ClearBuffers() {
	GLbitfield fClearFlags = 0;

	if (mfClearFlags & Render::CLEAR_COLOR) {
		fClearFlags |= GL_COLOR_BUFFER_BIT;
	}

	if (mfClearFlags & Render::CLEAR_DEPTH) {
		fClearFlags |= GL_DEPTH_BUFFER_BIT;
	}

	glClear(fClearFlags);
}

/*
	void RenderEngine::register_drawer(System& sys) {
		drawers.push_back(sys.drawer); // priority queue?	

		drawer:
			void draw();
	}

	(utility of this is that this can associate each system to drawing in a particular window)
*/

void RenderEngine::Startup() {
#ifdef _glfw3_h_
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mpWindow = glfwCreateWindow(mWindowWidth, mWindowHeight, mpcWindowName, nullptr, nullptr);

	if (mpWindow == nullptr) {
		std::cout << "failed to initialize glfw" << std::endl;
		std::exit(-1);
	}

	glfwMakeContextCurrent(mpWindow);
	glfwSetFramebufferSizeCallback(mpWindow, FramebufferCallback::FramebufferSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "failed to retrieve opengl funcs" << std::endl;
		std::exit(-1);
	}

	glViewport(0, 0, mWindowWidth, mWindowHeight);

#endif
}

RenderEngine& RenderEngine::Instance() {
	static RenderEngine gRenderEngine;
	return gRenderEngine;
}