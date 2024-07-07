#ifndef CAMERA_H
#define CAMERA_H
#include "component.h"
#include <glm/glm.hpp>

#include <vector>

class Transform;
class GameObject;
class Framebuffer;

class Camera : public Component {
private:
	std::vector<GameObject*> mViewables;

	// std::vector<Render::Command*> mCommands;

protected:
	Transform* mpTransform;
	Framebuffer* mpFramebuffer;
	int mWidth, mHeight;
	int mOriginX, mOriginY;

public:
	void Start() override;
	void Update() override;
	void ConstUpdate() const override;

	Camera(GameObject* pGO);

	void AddViewable(GameObject* pGO);

	inline void SetFramebuffer(Framebuffer* pFramebuffer) {
		mpFramebuffer = pFramebuffer;
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