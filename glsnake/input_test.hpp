#ifndef INPUT_TEST_HPP
#define INPUT_TEST_HPP
#include "component.h"

class GameObject;

class InputTest : public Component {
public:
	InputTest(GameObject* gameobject);
	virtual void start() override;
	virtual void update() override;
};

#endif