#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vector>

class Material;
class Mesh;
class Texture2D;

class Window {
protected:
	float mOriginX{ 0.5f }, mOriginY{ 0.5f }; // percentages
	float mWidth{ 0.5f }, mHeight{ 0.5f }; // percentages
	std::vector<Window*> mChildren{};

public:
	virtual void Draw() = 0;
	virtual void OnHover() { }
	virtual void OnClick() { }
	virtual void OnUnclick() { }
	virtual void OnUnhover() { }

	void AddChild(Window* pWindow) { mChildren.push_back(pWindow); }

	Window() { }
	virtual ~Window() { }
};

// child classes provide the texture(s)
class TexturedWindow : public Window {
private:
	Mesh* mpMesh{ nullptr }; // to be a plane
	Material* mpMaterial{ nullptr }; // to be a texture

protected:
	void SetTexture(Texture2D* pTexture);

public:
	virtual ~TexturedWindow() = 0;

	virtual void Draw() override;

	TexturedWindow();
};
#endif