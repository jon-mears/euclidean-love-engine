#include "selector.hpp"
#include "resourcemanager.hpp"
#include "framebuffer.hpp"
#include "texture.hpp"
#include "camera.h"

void Selector::start() {
	mpParentCamera = get_component<Camera>();

	Texture2D* pTexture = ResourceManager::instance().New<Texture2D>();
	Texture2D::ImageInfo info{};

	info.bGenMipmap = false;
	info.width = mpParentCamera->Width();
	info.height = mpParentCamera->Height();
	info.internal_format = GL_RGBA8;
	info.format = GL_RGBA8;

	mpFramebuffer = ResourceManager::instance().New<Framebuffer>();

	mpSelectorCamera = new GameObject();

	mpSelectorCamera->ShareAll(mpParentCamera);
	mpSelectorCamera->erase<Camera>();
	Camera* pCamera = mpSelectorCamera->add<Camera>();

	pCamera->SetFramebuffer(mpFramebuffer);

}