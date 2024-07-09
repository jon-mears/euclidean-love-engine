#include "window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <Windows.h>

namespace {
	void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}
}

Window::Window(std::string title, int width, int height, glm::vec4 bkgColor) : mTitle(title), mpWindow(nullptr), mWidth(width), mHeight(height), mBkgColor(bkgColor) { }

bool Window::ShouldClose() {
	return glfwWindowShouldClose(mpWindow);
}

void Window::SwapBuffers() {
	glfwSwapBuffers(mpWindow);
}

int Window::Width() {
	return mWidth;
}

int Window::Height() {
	return mHeight;
}

std::string Window::Title() {
	return mTitle;
}

int Window::GLInit() {
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mpWindow = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr);

	if (mpWindow == nullptr) {
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