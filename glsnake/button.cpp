#include "button.hpp"
#include "resource-manager.hpp"

Button::Button() : TexturedWindow{} { 
	mpInactiveTexture = ResourceManager::Instance().Retrieve
		<Texture2D>("Default Inactive Button Texture");
	mpHoverTexture = ResourceManager::Instance().Retrieve
		<Texture2D>("Default Hover Button Texture");
	mpActiveTexture = ResourceManager::Instance().Retrieve
		<Texture2D>("Default Active Button Texture");
}

void Button::SetInactiveTexture(Texture2D* pInactiveTexture) {
	mpInactiveTexture = pInactiveTexture;
}

void Button::SetHoverTexture(Texture2D* pHoverTexture) {
	mpHoverTexture = pHoverTexture;
}

void Button::SetActiveTexture(Texture2D* pActiveTexture) {
	mpActiveTexture = pActiveTexture;
}

void Button::OnHover() {
	SetTexture(mpHoverTexture);
}

void Button::OnUnhover() {
	SetTexture(mpInactiveTexture);
}

void Button::OnClick() {
	SetTexture(mpActiveTexture);
}