#ifndef TEXTURE2D_HPP
#define TEXTURE2D_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Image2D;

class Texture2D {
private:
	GLenum mWrapS = GL_REPEAT;
	GLenum mWrapT = GL_REPEAT;
	GLenum mMinFilter = GL_LINEAR_MIPMAP_LINEAR;
	GLenum mMagFilter = GL_LINEAR;

	GLuint mID;
	Image2D* mpIm;

public:
	void set_image(Image2D* im);
	void set_param(GLenum param, GLenum val);
	void compile();
	void enable();
	void disable();
};

#endif