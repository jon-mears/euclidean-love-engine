#include "selector-component.hpp"
#include "resource-manager.hpp"
#include "framebuffer.hpp"
#include "texture.hpp"
#include "camera-component.hpp"
#include "input-manager.hpp"
#include "editor-manager.hpp"
#include "shader-component.hpp"

#include <algorithm>
#include <glm/glm.hpp>

void SelectorComponent::Start() {
	mpParentCamera = GetComponent<CameraComponent>();

	mpTexture = ResourceManager::Instance().New<Texture2D>();
	Texture2D::ImageInfo info{};

	info.bGenMipmap = false;
	info.mipmap_level = 0;
	info.width = mpParentCamera->Width();
	info.height = mpParentCamera->Height();
	info.internal_format = GL_RGBA8;

	mpTexture->SetImage(info);

	Framebuffer* pFramebuffer = ResourceManager::Instance().New<Framebuffer>();

	pFramebuffer->ColorAttachment(mpTexture);

	mpSelectorObject = new GameObject();

	mpSelectorObject->ShareAllFrom(mpGO);
	mpSelectorObject->Erase<CameraComponent>();
	CameraComponent* pCamera = mpSelectorObject->Add<CameraComponent>();

	pCamera->SetFramebuffer(pFramebuffer);
	pCamera->SetViewport(mpParentCamera->OriginX(),
		mpParentCamera->OriginY(), mpParentCamera->Width(),
		mpParentCamera->Height());

	mpSelectorObject->Start();
}

void SelectorComponent::RegisterSelectable(GameObject* pGO) {
	CameraComponent* pCamera = mpSelectorObject->Retrieve<CameraComponent>();
	GameObject* pSelectable = new GameObject();

	pSelectable->ShareAllFrom(pGO);
	pSelectable->Erase<ShaderComponent>();
	ShaderComponent* pShaderComponent = 
		pSelectable->Add<ShaderComponent>();

	pShaderComponent->SetShader(ResourceManager::Instance().
		Retrieve<Shader>("Color Shader"));


	pCamera->AddViewable(pGO);
}

void SelectorComponent::Update() {
	mpSelectorObject->Update();

	if (InputManager::Instance().EventActive(Input::SELECT)) {
		glm::ivec2 mousepos{ InputManager::Instance().AbsoluteAxis(Input::HORIZONTAL), InputManager::Instance().AbsoluteAxis(Input::VERTICAL) };

		unsigned char *texel = mpTexture->ReadTexel(mousepos);
		glm::vec4 color{ texel[0], texel[1], texel[2], texel[3] };

		//if (mColor2Object.count(color)) {

		//	EditorManager::Instance().mpSelected = mColor2Object[color];
		//}
	}
}

void SelectorComponent::ConstUpdate() const { }

// MainCamera defined by the writer to the default framebuffer...
// ConstUpdate or Ordering (or BOTH!!!)