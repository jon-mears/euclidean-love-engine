#include "render-engine.hpp"
#include "resource-manager.hpp"
#include "targeted-camera-component.hpp"
#include "game-object.hpp"
#include "editor-manager.hpp"
#include "transform-component.hpp"
#include "glsl-translator.hpp"

#include "camera-component.hpp"
#include "primitives.hpp"

#include <iostream>
#include <string>
#include <map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

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

	//static GLuint local_vec_vao = 0;
	//static GLuint vbo = 0;

	//if (local_vec_vao == 0 && vbo == 0) {
	//	glGenBuffers(1, &vbo);
	//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 18,
	//		nullptr, GL_STATIC_DRAW);

	//	glGenVertexArrays(1, &local_vec_vao);
	//	glBindVertexArray(local_vec_vao);
	//	glVertexAttribPointer(GLSLTranslator::Attrib2Loc(
	//		Vertex::POSITION), 3, GL_FLOAT, GL_FALSE,
	//		3 * sizeof(GLfloat), (void*)0);
	//	glEnableVertexArrayAttrib(local_vec_vao,
	//		GLSLTranslator::Attrib2Loc(Vertex::POSITION));
	//}

	ClearBuffers();

	CameraComponent* pCamera = nullptr;
	for (std::map<std::string, GameObject*>::iterator it = ResourceManager::Instance().Begin<GameObject>(); it != ResourceManager::Instance().End<GameObject>(); ++it) {
		GameObject* pGO = it->second;

		if ((pCamera = pGO->Retrieve<CameraComponent>()) || (pCamera = pGO->Retrieve<TargetedCameraComponent>())) {
			pCamera->Draw();
		}
	}

	//DisableTests(GL_DEPTH_TEST);

	//if (EditorManager::Instance().mpSelected != nullptr) {
	//	TransformComponent* pTransformC =
	//		EditorManager::Instance().mpSelected->Retrieve<TransformComponent>();

	//	glm::vec3 position = pTransformC->Position(),
	//		localX = pTransformC->LocalX(),
	//		localY = pTransformC->LocalY(),
	//		localZ = pTransformC->LocalZ();

	//	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	//	glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * sizeof(GLfloat),
	//		glm::value_ptr(position));
	//	glBufferSubData(GL_ARRAY_BUFFER, 3 * sizeof(GLfloat),
	//		3 * sizeof(GLfloat), glm::value_ptr(localX));
	//	glBufferSubData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat),
	//		3 * sizeof(GLfloat), glm::value_ptr(position));
	//	glBufferSubData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat),
	//		3*sizeof(GLfloat, ))

	//	glm::vec3 localY = pTransformC->LocalY();
	//	glBufferSubData()
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