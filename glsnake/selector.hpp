#ifndef SELECTOR_HPP
#define SELECTOR_HPP
#include "component.h"
#include <map>

#include <glm/glm.hpp>

class Camera;
class Texture2D;
class GameObject;
class Framebuffer;

// @DEPENDENCY : CAMERA
class SelectorComponent : public Component {
private:
	Camera* mpParentCamera{ NULL };
	GameObject* mpSelectorObject{ NULL };
	Texture2D* mpTexture{ NULL };

	std::map<glm::vec4, GameObject*> mColor2Object{};

	glm::ivec4 mNextColor{ 1, 1, 1, 1};

public:
	virtual void Start() override;
	virtual void Update() override;

	void RegisterSelectable(GameObject* pGO);
};
#endif