#include "renderbuffer.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Renderbuffer::Renderbuffer() {
	glGenRenderbuffers(1, &mID);
}

void Renderbuffer::SetStorage(StorageInfo info) {
	Enable();
	glRenderbufferStorage(GL_RENDERBUFFER, info.internal_format, info.width, info.height);
	Disable();
}