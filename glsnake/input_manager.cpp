#include "input_manager.hpp"
#include "InputService.hpp"

InputManager::InputManager() { }

void InputManager::startup() { 
	mpInputService->startup();
}

InputManager& InputManager::instance() {
	static InputManager gInputManager;
	return gInputManager;
}