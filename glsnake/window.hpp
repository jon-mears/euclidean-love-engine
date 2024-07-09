#ifndef WINDOW_HPP
#define WINDOW_HPP

struct GLFWwindow;

#include <string>
#include <glm/glm.hpp>

class Window {
private:
	GLFWwindow* mpWindow;
	int mWidth, mHeight;
	std::string mTitle;
	glm::vec4 mBkgColor;

public:
	Window(std::string title, int width=500, int height=500, glm::vec4 bkgColor=glm::vec4{1.0f, 1.0f, 1.0f, 1.0f});
	bool ShouldClose();
	int Width();
	int Height();
	std::string Title();
	void SwapBuffers();

	int GLInit();

	friend class App;
};
#endif