#include "selector.hpp"
#include "resourcemanager.hpp"
#include "framebuffer.hpp"
#include "texture.hpp"
#include "camera.h"
#include "input_manager.hpp"

void SelectorComponent::Start() {
	mpParentCamera = GetComponent<Camera>();

	mpTexture = ResourceManager::instance().New<Texture2D>();
	Texture2D::ImageInfo info{};

	info.bGenMipmap = false;
	info.width = mpParentCamera->Width();
	info.height = mpParentCamera->Height();
	info.internal_format = GL_RGBA8;
	info.format = GL_RGBA8;

	mpTexture->SetImage(info);

	Framebuffer* pFramebuffer = ResourceManager::instance().New<Framebuffer>();

	pFramebuffer->ColorAttachment(mpTexture);

	mpSelectorCamera = new GameObject();

	mpSelectorCamera->ShareAll(mpGO);
	mpSelectorCamera->Erase<Camera>();
	Camera* pCamera = mpSelectorCamera->Add<Camera>();

	pCamera->SetFramebuffer(pFramebuffer);

	mpSelectorCamera->Start();
}

void SelectorComponent::Update() {
	mpSelectorCamera->Update();

	if (InputManager::instance().event_active(Input::SELECT)) {
		glm::ivec2 mousepos{ InputManager::instance().absolute_axis(Input::HORIZONTAL), InputManager::instance().absolute_axis(Input::VERTICAL) };

		mpTexture->Read(mousepos);
	}
}