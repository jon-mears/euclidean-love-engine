#ifndef OBJECT_EDITOR_HPP
#define OBJECT_EDITOR_HPP

#include "ui-window.hpp"

class GameObject;

class ObjectEditor : public UIWindow {
public:
	virtual void Draw() override;

	ObjectEditor();
};

#endif