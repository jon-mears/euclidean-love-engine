#include "texture.hpp"
#include "image.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Texture1D::Texture1D() {
	glGenTextures(1, &mID);

	Enable(); // set as texture1D
	Disable();

	for (std::map<GLenum, GLenum>::iterator it = mParamVals.begin(); it != mParamVals.end(); ++it) {
		GLenum eParam = it->first;
		GLenum eVal = it->second;

		SetParameter(eParam, eVal);
	}
}

void Texture1D::SetImage(Texture1D::ImageInfo info) {
	Enable();
	glTexImage1D(GL_TEXTURE_1D, 0, info.internal_format, info.width, 0, info.format,
		info.type, info.pImageData);
	if (info.bGenMipmap) {
		glGenerateMipmap(GL_TEXTURE_1D);
	}

	mInfo = info;

	Disable();
}

void Texture1D::SetImage(Image1D* pImage) {
	ImageInfo info{ pImage };

	Enable();
	glTexImage1D(GL_TEXTURE_1D, 0, info.internal_format, info.width, 0, info.format,
		info.type, info.pImageData);
	if (info.bGenMipmap) {
		glGenerateMipmap(GL_TEXTURE_1D);
	}

	mInfo = info;

	Disable();
}

void Texture1D::SetImage(Image1D& rImage) {
	ImageInfo info{ rImage };

	Enable();
	glTexImage1D(GL_TEXTURE_1D, 0, info.internal_format, info.width, 0, info.format,
		info.type, info.pImageData);
	if (info.bGenMipmap) {
		glGenerateMipmap(GL_TEXTURE_1D);
	}

	mInfo = info;

	Disable();
}

void Texture1D::SetParameter(GLenum eParam, GLenum eVal) {
	Enable();
	glTexParameteri(GL_TEXTURE_1D, eParam, eVal);
	Disable();
}

Texture2D::Texture2D() {
	glGenTextures(1, &mID);

	Enable(); // set as texture2D
	Disable();

	for (std::map<GLenum, GLenum>::iterator it = mParamVals.begin(); it != mParamVals.end(); ++it) {
		GLenum eParam = it->first;
		GLenum eVal = it->second;

		SetParameter(eParam, eVal);
	}
}

void Texture2D::SetImage(Texture2D::ImageInfo info) {
	Enable();

	glTexImage2D(GL_TEXTURE_2D, 0, info.internal_format, info.width, info.height, 0,
			info.format, info.type, info.pImageData);

	if (info.bGenMipmap) {
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	mInfo = info;

	Disable();
}

void Texture2D::SetImage(Image2D* pImage) {
	ImageInfo info{ pImage };

	Enable();
	glTexImage2D(GL_TEXTURE_2D, 0, info.internal_format, info.width, info.height, 0,
		info.format, info.type, info.pImageData);
	if (info.bGenMipmap) {
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	mInfo = info;

	Disable();
}

void Texture2D::SetImage(Image2D& rImage) {
	ImageInfo info{ rImage };

	Enable();
	glTexImage2D(GL_TEXTURE_2D, 0, info.internal_format, info.width, info.height, 0, 
		info.format, info.type, info.pImageData);
	if (info.bGenMipmap) {
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	mInfo = info;

	Disable();
}

void Texture2D::SetParameter(GLenum eParam, GLenum eVal) {
	Enable();
	glTexParameteri(GL_TEXTURE_2D, eParam, eVal);
	Disable();
}

void Texture2D::Read(glm::ivec2 position) {
	Enable();

	GLuint* pixel;

	//glGetTextureSubImage(GL_TEXTURE_2D, 0, position.x, 
	//	position.y, 0, 1, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, 1, &pixel);

	Disable();
}

unsigned char* Texture2D::ReadTexel(glm::ivec2 position) {
	Enable();

	static unsigned char data[4];

	//glGetTextureSubImage(GL_TEXTURE_2D, 0, position.x, position.y, 0,
	//	1, 1, 1, GL_RGBA8, GL_UNSIGNED_BYTE, 1, data);
	Disable();

	return data;
}

Texture3D::Texture3D() {
	glGenTextures(1, &mID);

	Enable(); // set as texture3D
	Disable();

	for (std::map<GLenum, GLenum>::iterator it = mParamVals.begin(); it != mParamVals.end(); ++it) {
		GLenum eParam = it->first;
		GLenum eVal = it->second;

		SetParameter(eParam, eVal);
	}
}

void Texture3D::SetImage(Texture3D::ImageInfo info) {
	Enable();
	glTexImage3D(GL_TEXTURE_3D, 0, info.internal_format, info.width, info.height,
		info.depth, 0, info.format, info.type, info.pImageData);
	if (info.bGenMipmap) {
		glGenerateMipmap(GL_TEXTURE_3D);
	}

	mInfo = info;

	Disable();
}

void Texture3D::SetImage(Image3D* pImage) {
	ImageInfo info{ pImage };

	Enable();
	glTexImage3D(GL_TEXTURE_3D, 0, info.internal_format, info.width, info.height, 
		info.depth, 0, info.format, info.type, info.pImageData);
	if (info.bGenMipmap) {
		glGenerateMipmap(GL_TEXTURE_3D);
	}

	mInfo = info;

	Disable();
}

void Texture3D::SetImage(Image3D& rImage) {
	ImageInfo info{ rImage };

	Enable();
	glTexImage3D(GL_TEXTURE_3D, 0, info.internal_format, info.width, info.height, 
		info.depth, 0, info.format, info.type, info.pImageData);
	if (info.bGenMipmap) {
		glGenerateMipmap(GL_TEXTURE_3D);
	}

	mInfo = info;

	Disable();
}

void Texture3D::SetParameter(GLenum eParam, GLenum eVal) {
	Enable();
	glTexParameteri(GL_TEXTURE_3D, eParam, eVal);
	Disable();
}