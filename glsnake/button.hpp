#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "window.hpp"
#include "texture.hpp"

class Button : public TexturedWindow {
private:
	Texture2D* mpInactiveTexture{ nullptr };
	Texture2D* mpHoverTexture{ nullptr };
	Texture2D* mpActiveTexture{ nullptr };

public:
	Button();

	void SetInactiveTexture(Texture2D* pInactiveTexture);
	void SetHoverTexture(Texture2D* pHoverTexture);
	void SetActiveTexture(Texture2D* pActiveTexture);

	virtual void OnHover() override;
	virtual void OnUnhover() override;
	virtual void OnClick() override;
};

#endif