#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <map>
#include <string>

#include "resourcemanager.hpp"
#include "resource.hpp"

#include <glm/glm.hpp>

class Image1D;
class Image2D;
class Image3D;

class Texture1D {
public:
	struct ImageInfo {
		Image1D* pImage;
		unsigned char* pImageData{ NULL };
		GLint mipmap_level{ 0 };
		GLint internal_format{ GL_RGBA };
		GLsizei width{ 0 };
		GLenum format{ GL_RGBA };
		GLenum type{ GL_UNSIGNED_BYTE };
		bool bGenMipmap{ true };

		ImageInfo(Image1D* apImage) : pImage(apImage) {
			if (apImage != NULL) {
				pImageData = apImage->Data();
				width = apImage->Width();
				format = apImage->Format();
				type = apImage->Type();
			}
		}

		ImageInfo(Image1D& rImage) : pImage(&rImage) {
			pImageData = rImage.Data();
			width = rImage.Width();
			format = rImage.Format();
			type = rImage.Type();
		}

		ImageInfo() : pImage(NULL) { }
	};

private:
	GLuint mID{ 0 };
	ImageInfo mInfo{};

	std::map<GLenum, GLenum> mParamVals{ {GL_TEXTURE_WRAP_S, GL_REPEAT},
		{GL_TEXTURE_WRAP_T, GL_REPEAT}, {GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR},
		{GL_TEXTURE_MAG_FILTER, GL_LINEAR} };

	friend Texture1D* ResourceManager::New<Texture1D>(const std::string);

public:
	Texture1D();
	void SetImage(ImageInfo info=ImageInfo());
	void SetImage(Image1D& rImage);
	void SetImage(Image1D* pImage);

	void SetParameter(GLenum eParam, GLenum eVal);

	inline void Enable() {
		glBindTexture(GL_TEXTURE_1D, mID);
	}

	inline void Disable() {
		glBindTexture(GL_TEXTURE_1D, 0);
	}

	inline int ID() { return mID; }

	inline operator GLuint() {
		return mID;
	}
};

class Texture2D {

public:
	struct ImageInfo {
		Image2D* pImage;
		unsigned char* pImageData{ NULL };
		GLint mipmap_level{ 0 };
		GLint internal_format{ GL_RGBA };
		GLsizei width{ 0 };
		GLsizei height{ 0 };
		GLenum format{ GL_RGBA };
		GLenum type{ GL_UNSIGNED_BYTE };
		bool bGenMipmap{ true };

		ImageInfo(Image2D* apImage) : pImage(apImage) {
			if (apImage != NULL) {
				pImageData = apImage->Data();
				width = apImage->Width();
				height = apImage->Height();
				format = apImage->Format();
				type = apImage->Type();
			}
		}

		ImageInfo(Image2D& rImage) : pImage(&rImage) {
			pImageData = rImage.Data();
			width = rImage.Width();
			height = rImage.Height();
			format = rImage.Format();
			type = rImage.Type();
		}

		ImageInfo() : pImage(NULL) { }
	};

private:
	GLuint mID{ 0 };
	ImageInfo mInfo{};
	std::map<GLenum, GLenum> mParamVals{ {GL_TEXTURE_WRAP_S, GL_REPEAT},
		{GL_TEXTURE_WRAP_T, GL_REPEAT}, {GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR},
		{GL_TEXTURE_MAG_FILTER, GL_LINEAR} };

	friend Texture2D* ResourceManager::New<Texture2D>(const std::string);

public:
	Texture2D();
	void SetImage(ImageInfo info=ImageInfo());
	void SetImage(Image2D& rImage);
	void SetImage(Image2D* pImage);
	void SetParameter(GLenum eParam, GLenum eVal);

	inline void Enable() {
		glBindTexture(GL_TEXTURE_2D, mID);
	}

	inline void Disable() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	inline int ID() { return mID; }

	inline operator GLuint() {
		return mID;
	}

	void Read(glm::ivec2 position);
	unsigned char* ReadTexel(glm::ivec2 position);
};

class Texture3D {
public:
	struct ImageInfo {
		Image3D* pImage;
		unsigned char* pImageData{ NULL };
		GLint mipmap_level{ 0 };
		GLint internal_format{ GL_RGBA };
		GLsizei width{ 0 };
		GLsizei height{ 0 };
		GLsizei depth{ 0 };
		GLenum format{ GL_RGBA };
		GLenum type{ GL_UNSIGNED_BYTE };
		bool bGenMipmap{ true };

		ImageInfo(Image3D* apImage) : pImage(apImage) {
			if (apImage != NULL) {
				pImageData = apImage->Data();
				width = apImage->Width();
				height = apImage->Height();
				depth = apImage->Depth();
				format = apImage->Format();
				type = apImage->Type();
			}
		}

		ImageInfo(Image3D& rImage) : pImage(&rImage) {
			pImageData = rImage.Data();
			width = rImage.Width();
			height = rImage.Height();
			depth = rImage.Depth();
			format = rImage.Format();
			type = rImage.Type();
		}

		ImageInfo() : pImage(NULL) { }
	};
private:
	GLuint mID{ 0 };
	ImageInfo mInfo{};
	std::map<GLenum, GLenum> mParamVals{ {GL_TEXTURE_WRAP_S, GL_REPEAT},
		{GL_TEXTURE_WRAP_T, GL_REPEAT}, {GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR},
		{GL_TEXTURE_MAG_FILTER, GL_LINEAR} };

	friend Texture3D* ResourceManager::New<Texture3D>(const std::string);

public:
	Texture3D();
	void SetImage(ImageInfo info=ImageInfo());
	void SetImage(Image3D &rImage);
	void SetImage(Image3D* pImage);
	void SetParameter(GLenum eParam, GLenum eVal);

	inline void Enable() {
		glBindTexture(GL_TEXTURE_3D, mID);
	}

	inline void Disable() {
		glBindTexture(GL_TEXTURE_3D, 0);
	}

	inline int ID() { return mID; }

	inline operator GLuint() {
		return mID;
	}
};

#endif