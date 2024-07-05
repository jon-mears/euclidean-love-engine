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

protected:
	Transform* mpTransform;
	Framebuffer* mpFramebuffer;
	int mWidth, mHeight;
	int mOriginX, mOriginY;

public:
	void start() override;
	void update() override;
	Camera(GameObject* gameobject);

	void add_viewable(GameObject* go);
	void SetFramebuffer(Framebuffer* pFrameBuffer);
	void SetViewport(const int x, const int y, const int width, const int height);

	void SetTests();

	void draw();
	virtual glm::mat4 view_matrix();

	inline int Height() { return mHeight; }
	inline int Width() { return mWidth; }
	
	// add in id?
};
#endif