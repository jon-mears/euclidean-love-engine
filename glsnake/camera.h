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

public:
	void start() override;
	void update() override;
	Camera(GameObject* gameobject);

	void add_viewable(GameObject* go);
	void SetFramebuffer(FrameBuffer* pFrameBuffer);
	void SetSize(const int width, const int height);

	void draw();
	virtual glm::mat4 view_matrix();
	
	// add in id?
};
#endif