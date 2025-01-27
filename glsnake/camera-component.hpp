#ifndef CAMERA_COMPONENT_HPP
#define CAMERA_COMPONENT_HPP
#include "component.hpp"
#include <glm/glm.hpp>

#include <vector>

class TransformComponent;
class GameObject;
class Framebuffer;

class CameraComponent : public Component {
private:
	std::vector<GameObject*> mViewables;

	// std::vector<Render::Command*> mCommands;

protected:
	TransformComponent* mpTransform;
	Framebuffer* mpFramebuffer{nullptr};
	int mWidth{ 600 }, mHeight{ 600 };
	int mOriginX{ 0 }, mOriginY{ 0 };

public:
	void Start() override;
	void Update() override;
	void ConstUpdate() const override;

	CameraComponent(GameObject* pGO);

	void AddViewable(GameObject* pGO);

	inline void SetFramebuffer(Framebuffer* pFramebuffer) {
		mpFramebuffer = pFramebuffer;
	}

	inline Framebuffer* GetFramebuffer() {
		return mpFramebuffer;
	}

	inline void SetViewport(const int x, const int y, const int width, const int height) {
		mOriginX = x; mOriginY = y;
		mWidth = width; mHeight = height;
	}

	void SetTests();

	void Draw();
	virtual glm::mat4 ViewMatrix();

	inline int Width() { return mWidth; }
	inline int Height() { return mHeight; }
	inline int OriginX() { return mOriginX; }
	inline int OriginY() { return mOriginY; }
	
	// add in id?
};
#endif