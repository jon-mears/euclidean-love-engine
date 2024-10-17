#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "resource.hpp"

struct ColorAttachmentInfo;
struct StencilInfo;
struct DepthInfo;
class Texture2D;
class Renderbuffer;

class Framebuffer {
private:
	GLuint mID;
public:
	Framebuffer();

	~Framebuffer() {
		glDeleteFramebuffers(1, &mID);
	}

	struct ColorAttachmentInfo {
		Texture2D* pTexture;
		Renderbuffer* pRenderbuffer;
		GLint mipmap_level{ 0 };
		GLint attachment{ 0 };

		ColorAttachmentInfo(Texture2D* apTexture) : pTexture(apTexture), pRenderbuffer(nullptr) { }
		ColorAttachmentInfo(Renderbuffer* apRenderbuffer) : pTexture(nullptr), pRenderbuffer(apRenderbuffer) { }
	};

	void ColorAttachment(ColorAttachmentInfo info);
	void ColorAttachment(Texture2D* pTexture);
	void ColorAttachment(Renderbuffer* pRenderbuffer);
	void ColorAttachment();

	struct DepthAttachmentInfo {
		Texture2D* pTexture;
		Renderbuffer* pRenderbuffer;
		GLint mipmap_level{ 0 };

		DepthAttachmentInfo(Texture2D* apTexture) : pTexture(apTexture), pRenderbuffer(nullptr) { }
		DepthAttachmentInfo(Renderbuffer* apRenderbuffer) : pTexture(nullptr), pRenderbuffer(apRenderbuffer) { }
	};

	void DepthAttachment(DepthAttachmentInfo info);
	void DepthAttachment(Texture2D* pTexture);
	void DepthAttachment(Renderbuffer* pRenderbuffer);
	void DepthAttachment();

	struct StencilAttachmentInfo {
		Texture2D* pTexture;
		Renderbuffer* pRenderbuffer;
		GLint mipmap_level{ 0 };

		StencilAttachmentInfo(Texture2D* apTexture) : pTexture(apTexture), pRenderbuffer(nullptr) { }
		StencilAttachmentInfo(Renderbuffer* apRenderbuffer) : pTexture(nullptr), pRenderbuffer(apRenderbuffer) { }
	};

	void StencilAttachment(StencilAttachmentInfo info);
	void StencilAttachment(Texture2D* pTexture);
	void StencilAttachment(Renderbuffer* pRenderbuffer);
	void StencilAttachment();

	struct DepthStencilAttachmentInfo {
		Texture2D* pTexture;
		Renderbuffer* pRenderbuffer;
		GLint mipmap_level{ 0 };

		DepthStencilAttachmentInfo(Texture2D* apTexture) : pTexture(apTexture), pRenderbuffer(nullptr) { }
		DepthStencilAttachmentInfo(Renderbuffer* apRenderbuffer) : pTexture(nullptr), pRenderbuffer(apRenderbuffer) { }
	};

	void DepthStencilAttachment(DepthStencilAttachmentInfo info);
	void DepthStencilAttachment(Texture2D* pTexture);
	void DepthStencilAttachment(Renderbuffer* pRenderbuffer);
	void DepthStencilAttachment();

	inline void Enable() { glBindFramebuffer(GL_FRAMEBUFFER, mID); }
	inline void Disable() { glBindFramebuffer(GL_FRAMEBUFFER, 0); }
	inline void EnableRead() { glBindFramebuffer(GL_READ_FRAMEBUFFER, mID); }
	inline void DisableRead() { glBindFramebuffer(GL_READ_FRAMEBUFFER, 0); }
	inline void EnableDraw() { glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mID); }
	inline void DisableDraw() { glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); }

	void CheckStatus();

	inline int ID() { return mID; }

	inline operator GLuint() {
		return mID;
	}

	inline bool operator==(const Framebuffer& rcRHS) {
		return mID == rcRHS.mID;
	}
};
#endif