#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include "resourcemanager.hpp"

class Image1D {
private:
	unsigned char* mData{NULL};
	int mWidth{0}, mNrChannels{0};
	GLenum mFormat{GL_RGBA}, mType{GL_UNSIGNED_BYTE};
	
	friend Image1D* ResourceManager::New<Image1D>(const std::string);

public:

	Image1D();
	void Open(const std::string filename);
	inline void Close() { stbi_image_free(mData); }
	inline int Width() { return mWidth; }
	inline int NrChannels() { return mNrChannels; }
	inline unsigned char* Data() { return mData; }
	inline GLenum Format() { return mFormat; }
	inline GLenum Type() { return mType; }
};

class Image2D {
private:
	unsigned char* mData{NULL};
	int mWidth{ 0 }, mHeight{ 0 }, mNrChannels{ 0 };
	GLenum mFormat{ GL_RGBA }, mType{ GL_UNSIGNED_BYTE };

	friend Image2D* ResourceManager::New<Image2D>(const std::string);

public:
	Image2D();
	void Open(const std::string filename);
	inline void Close() { stbi_image_free(mData); }
	inline int Width() { return mWidth; }
	inline int Height() { return mHeight; }
	inline int NrChannels() { return mNrChannels; }
	inline unsigned char* Data() { return mData; }
	inline GLenum Format() { return mFormat; }
	inline GLenum Type() { return mType; }
};

class Image3D {
private:
	unsigned char* mData{NULL};
	int mWidth{ 0 }, mHeight{ 0 }, mDepth{ 0 }, mNrChannels{ 0 };
	GLenum mFormat{ GL_RGBA }, mType{ GL_UNSIGNED_BYTE };

	friend Image3D* ResourceManager::New<Image3D>(const std::string);

public:
	Image3D();
	void Open(const std::string filename);
	inline void Close() { stbi_image_free(mData); }
	inline int Width() { return mWidth; }
	inline int Height() { return mHeight; }
	inline int Depth() { return mDepth; }
	inline int NrChannels() { return mNrChannels; }
	inline unsigned char* Data() { return mData; }
	inline GLenum Format() { return mFormat; }
	inline GLenum Type() { return mType; }
};
#endif