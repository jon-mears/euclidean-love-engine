#include "game.h"

#include <iostream>
#include <vector>
#include <algorithm>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace {
	void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
	}
}

int Game::glInit() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(600, 600, "GLSnake", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;

		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 600, 600);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	return 0;
}

int Game::init() {
	if (glInit() == -1) return -1;
	if (userInit() == -1) return -1;
	return 0;
}

void Game::process_input() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

void Game::loop() {
	while (!glfwWindowShouldClose(window)) {
		process_input();
		update();
		draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void Game::update() {
	std::for_each(objects.begin(), objects.end(), [](GameObject* go) {go->update();});
}

void Game::draw() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::deinit() {
	glfwTerminate();
}