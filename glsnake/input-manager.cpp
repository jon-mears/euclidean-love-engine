#include "input-manager.hpp"
#include "input-service.hpp"

InputManager::InputManager() { }

void InputManager::Startup() { 
	mpInputService->Startup();
}

InputManager& InputManager::Instance() {
	static InputManager gInputManager;
	return gInputManager;
}