#include "input_test.hpp"
#include "input_manager.hpp"
#include "gameobject.h"

#include <iostream>

InputTest::InputTest(GameObject* gameobject) : Component(gameobject) { }

void InputTest::start() { }

void InputTest::update() {
	if (InputManager::instance().event_active(Input::A_DOWN)) {
		std::cout << "A is down" << std::endl;
	}
	
	if (InputManager::instance().event_active(Input::B_PRESSED)) {
		std::cout << "B just pressed" << std::endl;
	}

	if (InputManager::instance().event_active(Input::SELECT)) {
		std::cout << "just selected" << std::endl;
	}
}