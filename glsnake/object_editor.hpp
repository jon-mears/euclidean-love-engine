#ifndef OBJECT_EDITOR_HPP
#define OBJECT_EDITOR_HPP

#include "ui_window.hpp"
class GameObject;

class ObjectEditor : public UIWindow {
public:
	virtual void draw() override;

	ObjectEditor();
};

#endif