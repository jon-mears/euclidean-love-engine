#ifndef ROTATOR_H
#define ROTATOR_H

#include <GLFW/glfw3.h>


class Rotator : public Component {
public:
	void update() override {
		auto t = go->get_component<Transform>();
		t->rotate(0.0f, glfwGetTime(), 0.0f);
	}
};
#endif