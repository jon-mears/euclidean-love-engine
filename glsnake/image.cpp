#include "image.hpp"
#include "stb_image.h"
#include <string>
#include <iostream>

void Image1D::Open(const std::string filename) {

	if (mData) {
		Close();
	}

	mData = stbi_load(filename.c_str(), &mWidth, NULL, &mNrChannels, 0);

	if (!mData) {
		std::cerr << "failed to load texture " << filename << std::endl;
		std::exit(-1);
	}
}

void Image2D::Open(const std::string filename) {

	if (mData) {
		Close();
	}

	mData = stbi_load(filename.c_str(), &mWidth, &mHeight, &mNrChannels, 0);

	if (!mData) {
		std::cerr << "failed to load texture " << filename << std::endl;
		std::exit(-1);
	}
}

void Image3D::Open(const std::string filename) {

	if (mData) {
		Close();
	}

	mData = stbi_load(filename.c_str(), &mWidth, &mHeight, &mNrChannels, 0);

	if (!mData) {
		std::cerr << "failed to load texture " << filename << std::endl;
		std::exit(-1);
	}
}