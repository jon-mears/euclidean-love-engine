#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "component.h"

class GameObject;

class Controller : public Component {
public:
	virtual void start() override;
	virtual void update() override;
	Controller(GameObject* gameobject);
};
#endif