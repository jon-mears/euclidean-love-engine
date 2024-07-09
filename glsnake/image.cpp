#include "image.hpp"
#include "stb_image.h"
#include <string>
#include <iostream>

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

	if (!mData) {
		std::cerr << "failed to load texture " << rcFilename << std::endl;
		std::exit(-1);
	}
}

void Image3D::Open(const std::string& rcFilename) {

	if (mData) {
		Close();
	}

	int width, int height, int nrChannels;

	mData = stbi_load(rcFilename.c_str(), &width, &height, &nrChannels, 0);

	mWidth = width;
	mHeight = height;
	mNrChannels = nrChannels;

	if (!mData) {
		std::cerr << "failed to load texture " << rcFilename << std::endl;
		std::exit(-1);
	}
}