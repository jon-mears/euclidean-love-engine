#ifndef RENDERBUFFER_HPP
#define RENDERBUFFER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "render-engine.hpp"

class Renderbuffer {
private:
	GLuint mID{ 0 };
public:

	struct StorageInfo {
		GLenum internal_format{ GL_RGBA4 };
		int width{ 0 };
		int height{ 0 };

		StorageInfo() {
			width = RenderEngine::Instance().WindowWidth();
			height = RenderEngine::Instance().WindowHeight();
		}
	};

	Renderbuffer();

	~Renderbuffer() {
		glDeleteRenderbuffers(1, &mID);
	}

	void SetStorage(StorageInfo info = StorageInfo());

	inline void Enable() {
		glBindRenderbuffer(GL_RENDERBUFFER, mID);
	}

	inline void Disable() {
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	inline operator GLuint() {
		return mID;
	}

	inline GLuint ID() {
		return mID;
	}
};
#endif