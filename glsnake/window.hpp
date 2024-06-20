#ifndef WINDOW_HPP
#define WINDOW_HPP

class GLFWwindow;

#include <string>
#include <glm/glm.hpp>

enum class Key {
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
};

class Window {
private:
	GLFWwindow* mpWindow;
	int mWidth, mHeight;
	std::string mTitle;
	glm::vec4 mBkgColor;

public:
	Window(std::string title, int width=500, int height=500, glm::vec4 bkgColor=glm::vec4{1.0f, 1.0f, 1.0f, 1.0f});
	bool should_close();
	int width();
	int height();
	bool press(Key k);
	std::string title();
	void swap_buffers();

	int glInit();
};
#endif