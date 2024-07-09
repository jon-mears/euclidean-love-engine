#ifndef SELECTOR_COMPONENT_HPP
#define SELECTOR_COMPONENT_HPP
#include "component.hpp"
#include <map>

#include <glm/glm.hpp>

class CameraComponent;
class Texture2D;
class GameObject;
class Framebuffer;

// @DEPENDENCY : CAMERA
class SelectorComponent : public Component {
private:
	CameraComponent* mpParentCamera{ nullptr };
	GameObject* mpSelectorObject{ nullptr };
	Texture2D* mpTexture{ nullptr };

	std::map<glm::vec4, GameObject*> mColor2Object{};

	glm::ivec4 mNextColor{ 1, 1, 1, 1};

public:
	virtual void Start() override;
	virtual void Update() override;

	void RegisterSelectable(GameObject* pGO);
};
#endif