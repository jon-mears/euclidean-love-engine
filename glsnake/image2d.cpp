#include "image2d.hpp"
#include "stb_image.h"
#include <string>
#include <iostream>

Image2D::Image2D(const std::string &filename) : mData(NULL), mWidth(0), mHeight(0), mNrChannels(0) {
	mData = stbi_load(filename.c_str(), &mWidth, &mHeight, &mNrChannels, 0);

	if (!mData) {
		std::cout << "failed to load texture " << filename << std::endl;
		std::exit(-1);
	}
}