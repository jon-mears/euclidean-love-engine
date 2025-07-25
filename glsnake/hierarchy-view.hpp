#ifndef HIERARCHY_VIEW_HPP
#define HIERARCHY_VIEW_HPP

#include <unordered_set>

#include "transform-component.hpp"
#include "game-object.hpp"

#include "ui-window.hpp"

class HierarchyView : public UIWindow {
private:
	std::unordered_set<GameObject*> mSelection{};
	GameObject* mpClicked{ nullptr };

	void DrawTree(TransformComponent* pTransformC);
	void DrawHierarchy();
	void DrawProperties();
public:
	virtual void Draw() override;
};

#endif