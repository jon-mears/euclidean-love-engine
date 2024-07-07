#include "selector.hpp"
#include "resourcemanager.hpp"
#include "framebuffer.hpp"
#include "texture.hpp"
#include "camera.h"
#include "input_manager.hpp"
#include "editor_manager.hpp"
#include "shadercomponent.h"

#include <algorithm>
#include <glm/glm.hpp>

void SelectorComponent::Start() {
	mpParentCamera = GetComponent<Camera>();

	mpTexture = ResourceManager::instance().New<Texture2D>();
	Texture2D::ImageInfo info{};

	info.bGenMipmap = false;
	info.mipmap_level = 0;
	info.width = mpParentCamera->Width();
	info.height = mpParentCamera->Height();
	info.internal_format = GL_RGBA8;

	mpTexture->SetImage(info);

	Framebuffer* pFramebuffer = ResourceManager::instance().New<Framebuffer>();

	pFramebuffer->ColorAttachment(mpTexture);

	mpSelectorObject = new GameObject();

	mpSelectorObject->ShareAllFrom(mpGO);
	mpSelectorObject->Erase<Camera>();
	Camera* pCamera = mpSelectorObject->Add<Camera>();

	pCamera->SetFramebuffer(pFramebuffer);
	pCamera->SetViewport(mpParentCamera->OriginX(),
		mpParentCamera->OriginY(), mpParentCamera->Width(),
		mpParentCamera->Height());

	mpSelectorObject->Start();
}

void SelectorComponent::RegisterSelectable(GameObject* pGO) {
	Camera* pCamera = mpSelectorObject->Retrieve<Camera>();
	GameObject* pSelectable = new GameObject();

	pSelectable->ShareAllFrom(pGO);
	pSelectable->Erase<ShaderComponent>();
	ShaderComponent* pShaderComponent = 
		pSelectable->Add<ShaderComponent>();

	pShaderComponent->SetShader(ResourceManager::instance().
		Retrieve<Shader>("Color Shader"));

	pShaderComponent->SetUniform()

	pCamera->AddViewable(pGO);
}

void SelectorComponent::Update() {
	mpSelectorObject->Update();

	if (InputManager::instance().event_active(Input::SELECT)) {
		glm::ivec2 mousepos{ InputManager::instance().absolute_axis(Input::HORIZONTAL), InputManager::instance().absolute_axis(Input::VERTICAL) };

		unsigned char *texel = mpTexture->ReadTexel(mousepos);
		glm::vec4 color{ texel[0], texel[1], texel[2], texel[3] };

		if (mColor2Object.count(color)) {

			EditorManager::instance().mpSelected = mColor2Object[color];
		}
	}
}

// MainCamera defined by the writer to the default framebuffer...
// ConstUpdate or Ordering (or BOTH!!!)