#include "window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace {
	void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}
}

Window::Window(std::string title, int width, int height, glm::vec4 bkgColor) : mTitle(title), mpWindow(NULL), mWidth(width), mHeight(height), mBkgColor(bkgColor) { }

bool Window::should_close() {
	return glfwWindowShouldClose(mpWindow);
}

void Window::swap_buffers() {
	glfwSwapBuffers(mpWindow);
}

int Window::width() {
	return mWidth;
}

int Window::height() {
	return mHeight;
}

std::string Window::title() {
	return mTitle;
}

int Window::glInit() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mpWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), NULL, NULL);

	if (mpWindow == NULL) {
		std::cout << "failed to create GLFW window" << std::endl;

		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(mpWindow);
	glfwSetFramebufferSizeCallback(mpWindow, framebuffer_size_callback);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(mpWindow, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	return 0;
}

bool Window::press(Key k) {
	switch (k) {
	case Key::A:
		return glfwGetKey(mpWindow, GLFW_KEY_A) == GLFW_PRESS;
		break;
	case Key::B:
		return glfwGetKey(mpWindow, GLFW_KEY_B) == GLFW_PRESS;
		break;
	case Key::C:
		return glfwGetKey(mpWindow, GLFW_KEY_C) == GLFW_PRESS;
		break;
	case Key::D:
		return glfwGetKey(mpWindow, GLFW_KEY_D) == GLFW_PRESS;
		break;
	case Key::E:
		return glfwGetKey(mpWindow, GLFW_KEY_E) == GLFW_PRESS;
		break;
	case Key::F:
		return glfwGetKey(mpWindow, GLFW_KEY_F) == GLFW_PRESS;
		break;
	case Key::G:
		return glfwGetKey(mpWindow, GLFW_KEY_G) == GLFW_PRESS;
		break;
	case Key::H:
		return glfwGetKey(mpWindow, GLFW_KEY_H) == GLFW_PRESS;
		break;
	case Key::I:
		return glfwGetKey(mpWindow, GLFW_KEY_I) == GLFW_PRESS;
		break;
	case Key::J:
		return glfwGetKey(mpWindow, GLFW_KEY_J) == GLFW_PRESS;
		break;
	case Key::K:
		return glfwGetKey(mpWindow, GLFW_KEY_K) == GLFW_PRESS;
		break;
	case Key::L:
		return glfwGetKey(mpWindow, GLFW_KEY_L) == GLFW_PRESS;
		break;
	case Key::M:
		return glfwGetKey(mpWindow, GLFW_KEY_M) == GLFW_PRESS;
		break;
	case Key::N:
		return glfwGetKey(mpWindow, GLFW_KEY_N) == GLFW_PRESS;
		break;
	case Key::O:
		return glfwGetKey(mpWindow, GLFW_KEY_O) == GLFW_PRESS;
		break;
	case Key::P:
		return glfwGetKey(mpWindow, GLFW_KEY_P) == GLFW_PRESS;
		break;
	case Key::Q:
		return glfwGetKey(mpWindow, GLFW_KEY_Q) == GLFW_PRESS;
		break;
	case Key::R:
		return glfwGetKey(mpWindow, GLFW_KEY_R) == GLFW_PRESS;
		break;
	case Key::S:
		return glfwGetKey(mpWindow, GLFW_KEY_S) == GLFW_PRESS;
		break;
	case Key::T:
		return glfwGetKey(mpWindow, GLFW_KEY_T) == GLFW_PRESS;
		break;
	case Key::U:
		return glfwGetKey(mpWindow, GLFW_KEY_U) == GLFW_PRESS;
		break;
	case Key::V:
		return glfwGetKey(mpWindow, GLFW_KEY_V) == GLFW_PRESS;
		break;
	case Key::W:
		return glfwGetKey(mpWindow, GLFW_KEY_W) == GLFW_PRESS;
		break;
	case Key::X:
		return glfwGetKey(mpWindow, GLFW_KEY_X) == GLFW_PRESS;
		break;
	case Key::Y:
		return glfwGetKey(mpWindow, GLFW_KEY_Y) == GLFW_PRESS;
		break;
	case Key::Z:
		return glfwGetKey(mpWindow, GLFW_KEY_Z) == GLFW_PRESS;
		break;
	}
}