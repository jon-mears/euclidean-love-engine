#include <string>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "image.hpp"
#include "stb_image.h"


void Image1D::Open(const std::string& rcFilename) {

	if (mData) {
		Close();
	}

	int width, nrChannels;
	mData = stbi_load(rcFilename.c_str(), &width, nullptr, &nrChannels, 0);

	mWidth = width;
	mNrChannels = nrChannels;

	if (!mData) {
		std::cerr << "failed to load texture " << rcFilename << std::endl;
		std::exit(-1);
	}

	switch (mNrChannels) {
	case 1:
		mFormat = GL_RED;
		break;
	case 2:
		mFormat = GL_RG;
		break;
	case 3:
		mFormat = GL_RGB;
		break;
	case 4:
		mFormat = GL_RGBA;
		break;
	default:
		mFormat = GL_RGBA;
		break;
	}
}

void Image2D::Open(const std::string& rcFilename) {

	if (mData) {
		Close();
	}

	int width, height, nrChannels;
	mData = stbi_load(rcFilename.c_str(), &width, &height, &nrChannels, 0);

	mWidth = width;
	mHeight = height;
	mNrChannels = nrChannels;

	std::cout << mNrChannels << std::endl;

	if (!mData) {
		std::cerr << "failed to load texture " << rcFilename << std::endl;
		std::exit(-1);
	}

	switch (mNrChannels) {
	case 1:
		mFormat = GL_RED;
		break;
	case 2:
		mFormat = GL_RG;
		break;
	case 3:
		mFormat = GL_RGB;
		break;
	case 4:
		mFormat = GL_RGBA;
		break;
	default:
		mFormat = GL_RGBA;
		break;
	}
}

void Image3D::Open(const std::string& rcFilename) {

	if (mData) {
		Close();
	}

	int width, height, nrChannels;

	mData = stbi_load(rcFilename.c_str(), &width, &height, &nrChannels, 0);

	mWidth = width;
	mHeight = height;
	mNrChannels = nrChannels;

	if (!mData) {
		std::cerr << "failed to load texture " << rcFilename << std::endl;
		std::exit(-1);
	}

	switch (mNrChannels) {
	case 1:
		mFormat = GL_RED;
		break;
	case 2:
		mFormat = GL_RG;
		break;
	case 3:
		mFormat = GL_RGB;
		break;
	case 4:
		mFormat = GL_RGBA;
		break;
	default:
		mFormat = GL_RGBA;
		break;
	}
}