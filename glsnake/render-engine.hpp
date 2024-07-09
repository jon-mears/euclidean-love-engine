#ifndef RENDER_ENGINE_HPP
#define RENDER_ENGINE_HPP

#include <glad/glad.h>
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

namespace FramebufferCallback {
	void FramebufferSizeCallback(GLFWwindow* pWindow, int width,
		int height);
}

// associate to each render engine a window???

class RenderEngine {
private:
	unsigned short mfClearFlags, mfTestFlags;
	int mWindowWidth, mWindowHeight;
	const char* mpcWindowName;

#ifdef _glfw3_h_
	GLFWwindow* mpWindow;
	inline void ProvideWindow(GLFWwindow* pWindow) {
		mpWindow = pWindow;
	}

#else
	void* mpWindow;
	inline void ProvideWindow(void* pWindow) {
		mpWindow = pWindow;
	}
#endif

	void Startup();
	void ClearBuffers();

	inline void WindowInfo(int width, int height, const char* pcName) {
		mWindowWidth = width;
		mWindowHeight = height;
		mpcWindowName = pcName;
	}

	RenderEngine();
	RenderEngine(RenderEngine& rhs) = delete;
	RenderEngine& operator=(RenderEngine& rhs) = delete;
	RenderEngine& operator=(RenderEngine rhs) = delete;

public:
	void Draw();

	inline GLFWwindow* Window() {
		return mpWindow;
	}

	inline int WindowWidth() {
		return mWindowWidth;
	}

	inline int WindowHeight() {
		return mWindowHeight;
	}

	inline void InitTests(unsigned short fTestFlags) {
		mfTestFlags |= fTestFlags;
	}

	inline void EnableTests(unsigned short fTestFlags) {
		if (Render::TEST_DEPTH & fTestFlags) {
			glEnable(GL_DEPTH_TEST);
		}
	}

	inline void DisableTests(unsigned short fTestFlags) {
		if (Render::TEST_DEPTH & fTestFlags) {
			glDisable(GL_DEPTH_TEST);
		}
	}

	inline void EnableClears(unsigned short fClearFlags) {
		mfClearFlags |= fClearFlags;
	}

	inline void DisableClears(unsigned short fClearFlags) {
		mfClearFlags &= ~fClearFlags;
	}

	inline void EndFrame() {
		SwapBuffers();
	}

	inline void SwapBuffers() {
#ifdef _glfw3_h_
		glfwSwapBuffers(mpWindow);
#endif
	}
	
	static RenderEngine& Instance();
	friend class App;
	friend void FramebufferCallback::FramebufferSizeCallback(GLFWwindow* pWindow, int width, int height);
};

#endif