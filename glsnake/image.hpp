#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

class Image1D {
private:
	unsigned char* mData{nullptr};
	int mWidth{0}, mNrChannels{0};
	GLenum mFormat{GL_RGBA}, mType{GL_UNSIGNED_BYTE};
	
public:
	Image1D() { };
	~Image1D() {
		Close();
	}

	void Open(const std::string& rcFilename);
	inline void Close() { stbi_image_free(mData); }
	inline int Width() { return mWidth; }
	inline int NrChannels() { return mNrChannels; }
	inline unsigned char* Data() { return mData; }
	inline GLenum Format() { return mFormat; }
	inline GLenum Type() { return mType; }
};

class Image2D {
private:
	unsigned char* mData{nullptr};
	int mWidth{ 0 }, mHeight{ 0 }, mNrChannels{ 0 };
	GLenum mFormat{ GL_RGBA }, mType{ GL_UNSIGNED_BYTE };

public:
	Image2D() { };
	~Image2D() {
		Close();
	}

	void Open(const std::string& rcFilename);
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
	unsigned char* mData{nullptr};
	int mWidth{ 0 }, mHeight{ 0 }, mDepth{ 0 }, mNrChannels{ 0 };
	GLenum mFormat{ GL_RGBA }, mType{ GL_UNSIGNED_BYTE };

public:
	Image3D() { };
	~Image3D() {
		Close();
	}

	void Open(const std::string& rcFilename);
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