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

	// for (std::vector<RenderCommand>::iterator it = 
	//	mRenderCommands.begin(); it != mRenderCommands.end();
	//	++it) {
	//		it->Execute();
	// }

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

// void RenderEngine::AddRenderCommand(RenderComponent* pRenderC) {
//	DrawCommand* pDrawCommand = new DrawCommand(pRenderC);
//	PreDrawCommand;
//	* must define operator< for DrawCommand and RenderCommand
//	
//	// static
//	it = FindCommandPosition(mRenderCommands.begin(),
//	mRenderCommands.end(), 
//		pDrawCommand);
//	
// 
//	RenderCommand* pPrevRenderCommand = nullptr;
//	
//	* SetupDrawCommand
//	
//	if (it != mRenderCommands.begin()) {
//		pPrevRenderCommand = *(it-1);
//	}
// 
//	mRenderCommands.insert(it, new RenderCommand(pPrevRenderCommand, 
//		pDrawCommand));
// 
// 
//	
// SetupCommand 
//	}

//// static
//std::vector<RenderCommand*>::iterator 
//RenderEngine::FindCommandPosition(std::vector<RenderCommand*>::iterator it1,
//	std::vector<RenderCommand*>::iterator it2, DrawCommand* pDrawCommand) {
//
//	const int cNPOS{ -1 };
//
//	int same_framebuffer{ cNPOS }, same_program{ cNPOS }, same_vao{ cNPOS }, 
//		same_mvp_matrix{ cNPOS }, same_vp_matrix{ cNPOS }, same_p_matrix{ cNPOS };
//
//	for (std::vector<RenderCommand*>::iterator it = it1; it != it2; ++it) {
//		if ((*it)->HasSameFramebufferAs(pDrawCommand)) {
//			same_framebuffer = it - it1;
//			same_program = cNPOS;
//			same_vao = cNPOS;
//			same_mvp_matrix = cNPOS;
//			same_vp_matrix = cNPOS;
//			same_p_matrix = cNPOS;
//		}
//
//		if ((*it)->HasSameProgramAs(pDrawCommand)) {
//			same_program = it - it1;
//			same_vao = cNPOS;
//			same_mvp_matrix = cNPOS;
//			same_vp_matrix = cNPOS;
//			same_p_matrix = cNPOS;
//		}
//
//		if ((*it)->HasSameVAOAs(pDrawCommand)) {
//			same_vao = it - it1;
//			same_mvp_matrix = cNPOS;
//			same_vp_matrix = cNPOS;
//			same_p_matrix = cNPOS;
//		}
//
//		if ((*it)->HasSameMVPMatrixAs(pDrawCommand)) {
//			same_mvp_matrix = it - it1;
//			same_vp_matrix = cNPOS;
//			same_p_matrix = cNPOS;
//		}
//
//		if ((*it)->HasSameVPMatrixAs(pDrawCommand)) {
//			same_vp_matrix = it - it1;
//			same_p_matrix = cNPOS;
//		}
//
//		if ((*it)->HasSamePMatrixAs(pDrawCommand)) {
//			same_p_matrix = it - it1;
//		}
//	}
//
//	// can potentially use the same statuses to determine the 
//	// necessary setup steps between draw commands
//
//	// given a change, need to update just the changed rendercommand and the next one
//
//	// need to return the index of the "bottommost similarity" that occurs within 
//	// the group of non -1 indices
//
//	int arrSimilarities[6] = { same_framebuffer, same_program, same_vao, same_mvp_matrix,
//	same_vp_matrix, same_p_matrix };
//
//	int index{ cNPOS };
//
//	for (size_t i = 0; i < 6; ++i) {
//		if (arrSimilarities[i] != cNPOS) {
//			index = arrSimilarities[i];
//		}
//
//		if (arrSimilarities[i] == cNPOS && index != cNPOS) {
//			return it1 + index;
//		}
//	}
//
//	return it1;
//}

// void RenderEngine::OptimizeRenderOrder()

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