#include "framebuffer.hpp"
#include "renderbuffer.hpp"
#include "texture.hpp"
#include "resource-manager.hpp"
#include "render-engine.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

Framebuffer::Framebuffer() {
	glGenFramebuffers(1, &mID);
}

void Framebuffer::ColorAttachment(ColorAttachmentInfo info) {
	Enable();
	
	if (info.pTexture != nullptr) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + info.attachment, GL_TEXTURE_2D, info.pTexture->ID(), info.mipmap_level);
	}

	else {
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + info.attachment, GL_RENDERBUFFER, info.pRenderbuffer->ID());
	}

	Disable();
}

void Framebuffer::ColorAttachment(Texture2D* pTexture) {
	ColorAttachmentInfo info{ pTexture };

	Enable();

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + info.attachment, GL_TEXTURE_2D, info.pTexture->ID(), info.mipmap_level);

	Disable();
}

void Framebuffer::ColorAttachment(Renderbuffer* pRenderbuffer) {
	ColorAttachmentInfo info{ pRenderbuffer };

	Enable();

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + info.attachment, GL_RENDERBUFFER, info.pRenderbuffer->ID());
}

void Framebuffer::ColorAttachment() {
	Texture2D* pTexture = ResourceManager::Instance().New<Texture2D>();
	Texture2D::ImageInfo img_info;
	img_info.width = RenderEngine::Instance().WindowWidth();
	img_info.height = RenderEngine::Instance().WindowHeight();
	img_info.bGenMipmap = false;

	pTexture->SetImage(img_info);

	ColorAttachmentInfo color_info(pTexture);

	Enable();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + color_info.attachment, GL_TEXTURE_2D, color_info.pTexture->ID(), color_info.mipmap_level);
	Disable();
}

void Framebuffer::DepthAttachment(DepthAttachmentInfo info) {
	Enable();

	if (info.pTexture != nullptr) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, info.pTexture->ID(), info.mipmap_level);
	}

	else {
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, info.pRenderbuffer->ID());
	}

	Disable();
}

void Framebuffer::DepthAttachment(Texture2D* pTexture) {
	DepthAttachmentInfo info{ pTexture };

	Enable();

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, info.pTexture->ID(), info.mipmap_level);

	Disable();
}

void Framebuffer::DepthAttachment(Renderbuffer* pRenderbuffer) {

	DepthAttachmentInfo info{ pRenderbuffer };
	Enable();

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, info.pRenderbuffer->ID());

	Disable();
}

void Framebuffer::DepthAttachment() {
	Texture2D* pTexture = ResourceManager::Instance().New<Texture2D>();

	Texture2D::ImageInfo img_info;
	img_info.width = RenderEngine::Instance().WindowWidth();
	img_info.height = RenderEngine::Instance().WindowHeight();
	img_info.format = GL_DEPTH_COMPONENT;
	img_info.internal_format = GL_DEPTH_COMPONENT;
	img_info.bGenMipmap = false;

	pTexture->SetImage(img_info);

	DepthAttachmentInfo depth_info(pTexture);

	Enable();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_info.pTexture->ID(), depth_info.mipmap_level);
	Disable();
}

void Framebuffer::StencilAttachment(StencilAttachmentInfo info) {
	Enable();
	
	if (info.pTexture != nullptr) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, info.pTexture->ID(), info.mipmap_level);
	}

	else {
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, info.pRenderbuffer->ID());
	}

	Disable();
}

void Framebuffer::StencilAttachment(Texture2D* pTexture) {
	StencilAttachmentInfo info{ pTexture };

	Enable();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, info.pTexture->ID(), info.mipmap_level);
	Disable();
}

void Framebuffer::StencilAttachment(Renderbuffer* pRenderbuffer) {
	StencilAttachmentInfo info{ pRenderbuffer };

	Enable();

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, info.pRenderbuffer->ID());
}

void Framebuffer::StencilAttachment() {
	Texture2D* pTexture = ResourceManager::Instance().New<Texture2D>();
	Texture2D::ImageInfo img_info;

	img_info.width = RenderEngine::Instance().WindowWidth();
	img_info.height = RenderEngine::Instance().WindowHeight();
	img_info.internal_format = GL_STENCIL_INDEX;
	img_info.format = GL_STENCIL_INDEX;
	img_info.bGenMipmap = false;

	pTexture->SetImage(img_info);

	StencilAttachmentInfo stencil_info(pTexture);

	Enable();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, stencil_info.pTexture->ID(), stencil_info.mipmap_level);
	Disable();
}

void Framebuffer::DepthStencilAttachment(DepthStencilAttachmentInfo info)
{
	Enable();

	if (info.pTexture != nullptr) {
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, info.pTexture->ID(), info.mipmap_level);
	}

	else {
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, info.pRenderbuffer->ID());
	}

	Disable();
}

void Framebuffer::DepthStencilAttachment(Texture2D* pTexture) {
	DepthStencilAttachmentInfo info(pTexture);

	Enable();

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, info.pTexture->ID(), info.mipmap_level);

	Disable();
}

void Framebuffer::DepthStencilAttachment(Renderbuffer* pRenderbuffer) {
	DepthStencilAttachmentInfo info{ pRenderbuffer };
	
	Enable();

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, info.pRenderbuffer->ID());

	Disable();
}

void Framebuffer::DepthStencilAttachment() {
	Texture2D* pTexture = ResourceManager::Instance().New<Texture2D>();

	Texture2D::ImageInfo img_info;
	img_info.width = RenderEngine::Instance().WindowWidth();
	img_info.height = RenderEngine::Instance().WindowHeight();
	img_info.internal_format = GL_DEPTH24_STENCIL8;
	img_info.format = GL_DEPTH24_STENCIL8;

	pTexture->SetImage(img_info);

	DepthStencilAttachmentInfo ds_info{ pTexture };

	Enable();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, ds_info.pTexture->ID(), ds_info.mipmap_level);
	Disable();
}

void Framebuffer::CheckStatus() {
	Enable();

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cerr << "framebuffer is incomplete!" << std::endl;
	}

	Disable();
}