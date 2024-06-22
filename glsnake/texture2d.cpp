#include "texture2d.hpp"
#include "image2d.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void Texture2D::set_image(Image2D* im) {
	mpIm = im;
}

void Texture2D::compile() {
	glGenTextures(1, &mID);
	glBindTexture(GL_TEXTURE_2D, mID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mWrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mWrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mMinFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mMagFilter);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mpIm->width(), mpIm->height(), 0, GL_RGB, GL_UNSIGNED_BYTE, mpIm->data());
	glGenerateMipmap(GL_TEXTURE_2D);
}

void Texture2D::set_param(GLenum param, GLenum val) {
	switch (param) {
	case GL_TEXTURE_WRAP_S:
		mWrapS = val;
		break;
	case GL_TEXTURE_WRAP_T:
		mWrapT = val;
		break;
	case GL_TEXTURE_MIN_FILTER:
		mMinFilter = val;
		break;
	case GL_TEXTURE_MAG_FILTER:
		mMagFilter = val;
		break;
	default:
		std::cout << "invalid enum parameter provided to Texture2D::set_param!" << std::endl;
		std::exit(-1);
		break;
	}
}

void Texture2D::enable() {
	glBindTexture(GL_TEXTURE_2D, mID);
}

void Texture2D::disable() {
	glBindTexture(GL_TEXTURE_2D, 0);
}