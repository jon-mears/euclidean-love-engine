#ifndef SELECTOR_HPP
#define SELECTOR_HPP
#include "component.h"

class Camera;
class Texture2D;
class GameObject;
class Framebuffer;

// @DEPENDENCY : CAMERA
class Selector : public Component {
private:
	Camera* mpParentCamera{ NULL };
	Framebuffer* mpFramebuffer{ NULL };
	GameObject* mpSelectorCamera{ NULL };
public:
	virtual void start() override;
	virtual void update() override;

	void RegisterSelectable(GameObject* pGO);
};
#endif