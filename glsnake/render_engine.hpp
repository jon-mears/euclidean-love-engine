#ifndef RENDER_ENGINE_HPP
#define RENDER_ENGINE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <GLFW/glfw3.h>

namespace Render {
	enum Clear {
		CLEAR_COLOR = 0x0001,
		CLEAR_DEPTH = 0x0002
	};

	enum Test {
		TEST_DEPTH = 0x0001
	};
}

// associate to each render engine a window???

class RenderEngine {
private:
	unsigned short mClearFlags, mTestFlags;
	int mWindowWidth, mWindowHeight;
	const char* mpcWindowName;

#ifdef _glfw3_h_
	GLFWwindow* mpWindow;
	inline void provide_window(GLFWwindow* pWindow) {
		mpWindow = pWindow;
	}

#else
	void* mpWindow;
	inline void provide_window(void* pWindow) {
		mpWindow = pWindow;
	}
#endif

	void startup();
	void clear_buffers();

	inline void window_info(int width, int height, const char* pName) {
		mWindowWidth = width;
		mWindowHeight = height;
		mpcWindowName = pName;
	}

	RenderEngine();
	RenderEngine(RenderEngine& rhs) = delete;
	RenderEngine& operator=(RenderEngine& rhs) = delete;
	RenderEngine& operator=(RenderEngine rhs) = delete;

public:
	void draw();

	inline void init_tests(unsigned short test_flags) {
		mTestFlags |= test_flags;
	}

	inline void enable_tests(unsigned short test_flags) {
		if (Render::TEST_DEPTH & test_flags) {
			glEnable(GL_DEPTH_TEST);
		}
	}

	inline void disable_tests(unsigned short test_flags) {
		if (Render::TEST_DEPTH & test_flags) {
			glDisable(GL_DEPTH_TEST);
		}
	}

	inline void enable_clears(unsigned short clear_flags) {
		mClearFlags |= clear_flags;
	}

	inline void disable_clears(unsigned short clear_flags) {
		mClearFlags &= ~clear_flags;
	}

	inline void end_frame() {
		swap_buffers();
	}

	inline void swap_buffers() {
#ifdef _glfw3_h_
		glfwSwapBuffers(mpWindow);
#endif
	}
	
	static RenderEngine& instance();
	friend class Game;
};

#endif