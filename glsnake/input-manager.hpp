#ifndef INPUT_MANAGER_HPP
#define INPUT_MANAGER_HPP

#include "input-service.hpp"

class InputService;

namespace Input {
	// should be described outside any particualr input system 
	// (the keys stuff can be implemented with a virtual keyboard 
	// on a gamepad)
	enum Event {
		SELECT,
		A_DOWN,
		A_PRESSED,
		A_RELEASED,
		B_DOWN,
		B_PRESSED,
		B_RELEASED,
		C_DOWN,
		C_PRESSED,
		C_RELEASED,
		D_DOWN,
		D_PRESSED,
		D_RELEASED,
		E_DOWN,
		E_PRESSED,
		E_RELEASED,
		F_DOWN,
		F_PRESSED,
		F_RELEASED,
		G_HELD,
		G_PRESSED,
		G_RELEASED,
		H_HELD,
		H_DOWN,
		H_RELEASED,
		I_DOWN,
		I_PRESSED,
		I_RELEASED,
		J_DOWN,
		J_PRESSED,
		J_RELEASED,
		K_DOWN,
		K_PRESSED,
		K_RELEASED,
		L_DOWN,
		L_PRESSED,
		L_RELEASED,
		M_DOWN,
		M_PRESSED,
		M_RELEASED,
		N_DOWN,
		N_PRESSED,
		N_RELEASED,
		O_DOWN,
		O_PRESSED,
		O_RELEASED,
		P_DOWN,
		P_PRESSED,
		P_RELEASED,
		Q_DOWN,
		Q_PRESSED,
		Q_RELEASED,
		R_DOWN,
		R_PRESSED,
		R_RELEASED,
		S_DOWN,
		S_PRESSED,
		S_RELEASED,
		T_DOWN,
		T_PRESSED,
		T_RELEASED,
		U_DOWN,
		U_PRESSED,
		U_RELEASED,
		V_DOWN,
		V_PRESSED,
		V_RELEASED,
		W_DOWN,
		W_PRESSED,
		W_RELEASED,
		X_DOWN,
		X_PRESSED,
		X_RELEASED,
		Y_DOWN,
		Y_PRESSED,
		Y_RELEASED,
		Z_DOWN,
		Z_PRESSED,
		Z_RELEASED,
		PANNING,
		ORBITING,
		LOOKING
	};

	enum Axis {
		HORIZONTAL,
		VERTICAL
	};
}

class InputManager {
private:
	InputManager();
	InputManager(InputManager& lhs) = delete;
	InputManager& operator=(InputManager& lhs) = delete;
	InputManager& operator=(InputManager lhs) = delete;

	InputService* mpInputService;

#ifdef _glfw3_h_
	GLFWwindow* mpWindow;
	inline void ProvideWindow(GLFWwindow* pWindow) {
		mpWindow = pWindow;
	}

#else // not GLFW3
	void* mpWindow;
	inline void ProvideWindow(void* pWindow) {
		mpWindow = pWindow;
	}
#endif

	void Startup();

public:
	static InputManager& Instance();
	inline void ProvideService(InputService* pInputService) {
		mpInputService = pInputService;
	}

	inline void PollEvents() {
		mpInputService->PollEvents();
	}

	inline bool EventActive(Input::Event eEvent) {
		return mpInputService->EventActive(eEvent);
	}

	inline float AbsoluteAxis(Input::Axis eAxis) {
		return mpInputService->AbsoluteAxis(eAxis);
	}

	inline float RelativeAxis(Input::Axis eAxis) {
		return mpInputService->RelativeAxis(eAxis);
	}

	inline void StartFrame() {
		PollEvents();
	}

#ifdef _glfw3_h_
	inline GLFWwindow* Window() {
		return mpWindow;
	}
#else
	inline void* Window() {
		return mpWindow;
	}
#endif

	friend class App;
};
#endif