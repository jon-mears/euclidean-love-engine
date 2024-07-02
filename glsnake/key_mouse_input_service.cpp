#include "key_mouse_input_service.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "input_manager.hpp"

#include <iostream>

namespace {
	enum Key {
		NONE = 0x0000000000000000,
		A = 0x0000000000000001,
		B = 0x0000000000000002,
		C = 0x0000000000000004,
		D = 0x0000000000000008,
		E = 0x0000000000000010, 
		F = 0x0000000000000020, 
		G = 0x0000000000000040, 
		H = 0x0000000000000080, 
		I = 0x0000000000000100,
		J = 0x0000000000000200,
		K = 0x0000000000000400,
		L = 0x0000000000000800,
		M = 0x0000000000001000,
		N = 0x0000000000002000,
		O = 0x0000000000004000,
		P = 0x0000000000008000, 
		Q = 0x0000000000010000,
		R = 0x0000000000020000, 
		S = 0x0000000000040000, 
		T = 0x0000000000080000, 
		U = 0x0000000000100000, 
		V = 0x0000000000200000, 
		W = 0x0000000000400000, 
		X = 0x0000000000800000, 
		Y = 0x0000000001000000, 
		Z = 0x0000000002000000, 
		UP = 0x0000000004000000, 
		DOWN = 0x0000000008000000, 
		LEFT = 0x00000000010000000, 
		RIGHT = 0x0000000002000000, 
		LEFT_MOUSE_BUTTON = 0x0000000004000000, 
		MIDDLE_MOUSE_BUTTON = 0x0000000008000000,
		RIGHT_MOUSE_BUTTON = 0x0000000010000000,
		LEFT_SHIFT = 0x0000000020000000,
		LEFT_CTRL = 0x0000000040000000
	};

#ifdef _glfw3_h_
	typedef GLFWkeyfun KeyCallback;
	typedef GLFWmousebuttonfun MouseButtonCallback;
	typedef GLFWcursorposfun CursorPosCallback;
#endif
}

// can handle chords
bool KeyMouseInputService::is_down(unsigned long include, unsigned long exclude) {
	return ((mButtons & include) == include) && ((mButtons & exclude) == NONE);
}

// maybe action is a better word
bool KeyMouseInputService::event_active(Input::Event event) {
	switch (event) {
	case Input::SELECT:
		return pressed(LEFT_MOUSE_BUTTON);
	case Input::A_DOWN:
		return is_down(A);
	case Input::A_PRESSED:
		return pressed(A);
	case Input::B_PRESSED:
		return pressed(B);
	case Input::PANNING:
		return is_down(MIDDLE_MOUSE_BUTTON | LEFT_SHIFT);
	case Input::ORBITING:
		return is_down(MIDDLE_MOUSE_BUTTON, LEFT_SHIFT | LEFT_CTRL);
	case Input::LOOKING:
		return is_down(MIDDLE_MOUSE_BUTTON | LEFT_CTRL);
	default:
		std::cout << "input event not yet implemented!" << std::endl;
	}

	return false;
}

// can handle chords
bool KeyMouseInputService::pressed(unsigned long include, unsigned long exclude) {
	return ((mButtonDowns & include) == include) && ((mButtonDowns & exclude) == NONE);
}

// can handle chords
bool KeyMouseInputService::released(unsigned long include, unsigned long exclude) {
	return ((mButtonUps & include) == include) && ((mButtonUps & exclude) == NONE);
}

float KeyMouseInputService::absolute_axis(Input::Axis axis) {
	switch (axis) {
	case Input::HORIZONTAL:
		return mXMousePos;
	case Input::VERTICAL:
		return mYMousePos;
	default:
		return 0.0f;
	}
}

float KeyMouseInputService::relative_axis(Input::Axis axis) {
	switch (axis) {
	case Input::HORIZONTAL:
		return mXMousePos - mPrevXMousePos;
	case Input::VERTICAL:
		return mYMousePos - mPrevYMousePos;
	default:
		return 0.0f;
	}
}

#ifdef _glfw3_h_ // if GLFW3...
void KeyMouseInputService::poll_events() {
	glfwPollEvents();

	mPrevButtons = mButtons;
	mPrevXMousePos = mXMousePos;
	mPrevYMousePos = mYMousePos;

	mButtons = mBButtons;
	mXMousePos = mBXMousePos;
	mYMousePos = mBYMousePos;

	mButtonDowns = mButtons & (mButtons ^ mPrevButtons);
	mButtonUps = ~mButtons & (mButtons ^ mPrevButtons);
}

void KeyMouseInputService::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (mPrevKeyCallback != NULL) {
		mPrevKeyCallback(window, key, scancode, action, mods);
	}
	
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_A:
			mBButtons |= A;
			break;
		case GLFW_KEY_B:
			mBButtons |= B;
			break;
		case GLFW_KEY_C:
			mBButtons |= C;
			break;
		case GLFW_KEY_D:
			mBButtons |= D;
			break;
		case GLFW_KEY_E:
			mBButtons |= E;
			break;
		case GLFW_KEY_F:
			mBButtons |= F;
			break;
		case GLFW_KEY_G:
			mBButtons |= G;
			break;
		case GLFW_KEY_H:
			mBButtons |= H;
			break;
		case GLFW_KEY_I:
			mBButtons |= I;
			break;
		case GLFW_KEY_J:
			mBButtons |= J;
			break;
		case GLFW_KEY_K:
			mBButtons |= K;
			break;
		case GLFW_KEY_L:
			mBButtons |= L;
			break;
		case GLFW_KEY_M:
			mBButtons |= M;
			break;
		case GLFW_KEY_N:
			mBButtons |= N;
			break;
		case GLFW_KEY_O:
			mBButtons |= O;
			break;
		case GLFW_KEY_P:
			mBButtons |= P;
			break;
		case GLFW_KEY_Q:
			mBButtons |= Q;
			break;
		case GLFW_KEY_R:
			mBButtons |= R;
			break;
		case GLFW_KEY_S:
			mBButtons |= S;
			break;
		case GLFW_KEY_T:
			mBButtons |= T;
			break;
		case GLFW_KEY_U:
			mBButtons |= U;
			break;
		case GLFW_KEY_V:
			mBButtons |= V;
			break;
		case GLFW_KEY_W:
			mBButtons |= W;
			break;
		case GLFW_KEY_X:
			mBButtons |= X;
			break;
		case GLFW_KEY_Y:
			mBButtons |= Y;
			break;
		case GLFW_KEY_Z:
			mBButtons |= Z;
			break;
		case GLFW_KEY_UP:
			mBButtons |= UP;
			break;
		case GLFW_KEY_DOWN:
			mBButtons |= DOWN;
			break;
		case GLFW_KEY_LEFT:
			mBButtons |= LEFT;
			break;
		case GLFW_KEY_RIGHT:
			mBButtons |= RIGHT;
			break;
		case GLFW_KEY_LEFT_SHIFT:
			mBButtons |= LEFT_SHIFT;
			break;
		case GLFW_KEY_LEFT_CONTROL:
			mBButtons |= LEFT_CTRL;
			break;
		default:
			break;
		}
	}

	else if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_A:
			mBButtons &= ~A;
			break;
		case GLFW_KEY_B:
			mBButtons &= ~B;
			break;
		case GLFW_KEY_C:
			mBButtons &= ~C;
			break;
		case GLFW_KEY_D:
			mBButtons &= ~D;
			break;
		case GLFW_KEY_E:
			mBButtons &= ~E;
			break;
		case GLFW_KEY_F:
			mBButtons &= ~F;
			break;
		case GLFW_KEY_G:
			mBButtons &= ~G;
			break;
		case GLFW_KEY_H:
			mBButtons &= ~H;
			break;
		case GLFW_KEY_I:
			mBButtons &= ~I;
			break;
		case GLFW_KEY_J:
			mBButtons &= ~J;
			break;
		case GLFW_KEY_K:
			mBButtons &= ~K;
			break;
		case GLFW_KEY_L:
			mBButtons &= ~L;
			break;
		case GLFW_KEY_M:
			mBButtons &= ~M;
			break;
		case GLFW_KEY_N:
			mBButtons &= ~N;
			break;
		case GLFW_KEY_O:
			mBButtons &= ~O;
			break;
		case GLFW_KEY_P:
			mBButtons &= ~P;
			break;
		case GLFW_KEY_Q:
			mBButtons &= ~Q;
			break;
		case GLFW_KEY_R:
			mBButtons &= ~R;
			break;
		case GLFW_KEY_S:
			mBButtons &= ~S;
			break;
		case GLFW_KEY_T:
			mBButtons &= ~T;
			break;
		case GLFW_KEY_U:
			mBButtons &= ~U;
			break;
		case GLFW_KEY_V:
			mBButtons &= ~V;
			break;
		case GLFW_KEY_W:
			mBButtons &= ~W;
			break;
		case GLFW_KEY_X:
			mBButtons &= ~X;
			break;
		case GLFW_KEY_Y:
			mBButtons &= ~Y;
			break;
		case GLFW_KEY_Z:
			mBButtons &= ~Z;
			break;
		case GLFW_KEY_UP:
			mBButtons &= ~UP;
			break;
		case GLFW_KEY_DOWN:
			mBButtons &= ~DOWN;
			break;
		case GLFW_KEY_LEFT:
			mBButtons &= ~LEFT;
			break;
		case GLFW_KEY_RIGHT:
			mBButtons &= ~RIGHT;
			break;
		case GLFW_KEY_LEFT_SHIFT:
			mBButtons &= ~LEFT_SHIFT;
			break;
		case GLFW_KEY_LEFT_CONTROL:
			mBButtons &= ~LEFT_CTRL;
		default:
			break;
		}
	}
}

void KeyMouseInputService::mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (mPrevMouseButtonCallback != NULL) {
		mPrevMouseButtonCallback(window, button, action, mods);
	}
	
	if (action == GLFW_PRESS) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT:
			mBButtons |= LEFT_MOUSE_BUTTON;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			mBButtons |= MIDDLE_MOUSE_BUTTON;
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			mBButtons |= RIGHT_MOUSE_BUTTON;
			break;
		default:
			break;
		}
	}

	else if (action == GLFW_RELEASE) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT:
			mBButtons &= ~LEFT_MOUSE_BUTTON;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			mBButtons &= ~MIDDLE_MOUSE_BUTTON;
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			mBButtons &= ~RIGHT_MOUSE_BUTTON;
			break;
		default:
			break;
		}
	}
}

void KeyMouseInputService::cursor_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	if (mPrevCursorPosCallback != NULL) {
		mPrevCursorPosCallback(window, xpos, ypos);
	}
	
	mBXMousePos = xpos;
	mBYMousePos = ypos;
}

void KeyMouseInputService::startup() {
	glfwSetWindowUserPointer(InputManager::instance().window(), this);

	mPrevKeyCallback = glfwSetKeyCallback(InputManager::instance().window(), KeyMouseInputService::key_callback_forwarder);

	mPrevMouseButtonCallback = glfwSetMouseButtonCallback(InputManager::instance().window(), KeyMouseInputService::mouse_button_callback_forwarder);

	mPrevCursorPosCallback = glfwSetCursorPosCallback(InputManager::instance().window(), KeyMouseInputService::cursor_pos_callback_forwarder);
}

void KeyMouseInputService::key_callback_forwarder(GLFWwindow* window, int key, int scancode, int action, int mods) {
	KeyMouseInputService* service = static_cast<KeyMouseInputService*>(glfwGetWindowUserPointer(window));

	service->key_callback(window, key, scancode, action, mods);
}

void KeyMouseInputService::mouse_button_callback_forwarder(GLFWwindow* window, int button, int action, int mods) {
	KeyMouseInputService* pService = static_cast<KeyMouseInputService*>(glfwGetWindowUserPointer(window));

	pService->mouse_button_callback(window, button, action, mods);
}

void KeyMouseInputService::cursor_pos_callback_forwarder(GLFWwindow* window, double xpos, double ypos) {
	KeyMouseInputService* pService = static_cast<KeyMouseInputService*>(glfwGetWindowUserPointer(window));
	pService->cursor_pos_callback(window, xpos, ypos);
}

#else // not GLFW3

void KeyMouseInputService::poll_events() { }
#endif // end platform-/framework-specific