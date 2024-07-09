#include "key-mouse-input-service.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "input-manager.hpp"

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
bool KeyMouseInputService::IsDown(unsigned long include, unsigned long exclude) {
	return ((mButtons & include) == include) && ((mButtons & exclude) == NONE);
}

// maybe action is a better word
bool KeyMouseInputService::EventActive(Input::Event eEvent) {
	switch (eEvent) {
	case Input::SELECT:
		return Pressed(LEFT_MOUSE_BUTTON);
	case Input::A_DOWN:
		return IsDown(A);
	case Input::A_PRESSED:
		return Pressed(A);
	case Input::B_PRESSED:
		return Pressed(B);
	case Input::PANNING:
		return IsDown(MIDDLE_MOUSE_BUTTON | LEFT_SHIFT);
	case Input::ORBITING:
		return IsDown(MIDDLE_MOUSE_BUTTON, LEFT_SHIFT | LEFT_CTRL);
	case Input::LOOKING:
		return IsDown(MIDDLE_MOUSE_BUTTON | LEFT_CTRL);
	default:
		std::cout << "input event not yet implemented!" << std::endl;
	}

	return false;
}

// can handle chords
bool KeyMouseInputService::Pressed(unsigned long include, unsigned long exclude) {
	return ((mButtonDowns & include) == include) && ((mButtonDowns & exclude) == NONE);
}

// can handle chords
bool KeyMouseInputService::Released(unsigned long include, unsigned long exclude) {
	return ((mButtonUps & include) == include) && ((mButtonUps & exclude) == NONE);
}

float KeyMouseInputService::AbsoluteAxis(Input::Axis eAxis) {
	switch (eAxis) {
	case Input::HORIZONTAL:
		return mXMousePos;
	case Input::VERTICAL:
		return mYMousePos;
	default:
		return 0.0f;
	}
}

float KeyMouseInputService::RelativeAxis(Input::Axis eAxis) {
	switch (eAxis) {
	case Input::HORIZONTAL:
		return mXMousePos - mPrevXMousePos;
	case Input::VERTICAL:
		return mYMousePos - mPrevYMousePos;
	default:
		return 0.0f;
	}
}

#ifdef _glfw3_h_ // if GLFW3...
void KeyMouseInputService::PollEvents() {
	glfwPollEvents();

	mPrevButtons = mButtons;
	mPrevXMousePos = mXMousePos;
	mPrevYMousePos = mYMousePos;

	mButtons = mBufButtons;
	mXMousePos = mBufXMousePos;
	mYMousePos = mBufYMousePos;

	mButtonDowns = mButtons & (mButtons ^ mPrevButtons);
	mButtonUps = ~mButtons & (mButtons ^ mPrevButtons);
}

void KeyMouseInputService::KeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mods) {
	if (mPrevKeyCallback != nullptr) {
		mPrevKeyCallback(pWindow, key, scancode, action, mods);
	}
	
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_A:
			mBufButtons |= A;
			break;
		case GLFW_KEY_B:
			mBufButtons |= B;
			break;
		case GLFW_KEY_C:
			mBufButtons |= C;
			break;
		case GLFW_KEY_D:
			mBufButtons |= D;
			break;
		case GLFW_KEY_E:
			mBufButtons |= E;
			break;
		case GLFW_KEY_F:
			mBufButtons |= F;
			break;
		case GLFW_KEY_G:
			mBufButtons |= G;
			break;
		case GLFW_KEY_H:
			mBufButtons |= H;
			break;
		case GLFW_KEY_I:
			mBufButtons |= I;
			break;
		case GLFW_KEY_J:
			mBufButtons |= J;
			break;
		case GLFW_KEY_K:
			mBufButtons |= K;
			break;
		case GLFW_KEY_L:
			mBufButtons |= L;
			break;
		case GLFW_KEY_M:
			mBufButtons |= M;
			break;
		case GLFW_KEY_N:
			mBufButtons |= N;
			break;
		case GLFW_KEY_O:
			mBufButtons |= O;
			break;
		case GLFW_KEY_P:
			mBufButtons |= P;
			break;
		case GLFW_KEY_Q:
			mBufButtons |= Q;
			break;
		case GLFW_KEY_R:
			mBufButtons |= R;
			break;
		case GLFW_KEY_S:
			mBufButtons |= S;
			break;
		case GLFW_KEY_T:
			mBufButtons |= T;
			break;
		case GLFW_KEY_U:
			mBufButtons |= U;
			break;
		case GLFW_KEY_V:
			mBufButtons |= V;
			break;
		case GLFW_KEY_W:
			mBufButtons |= W;
			break;
		case GLFW_KEY_X:
			mBufButtons |= X;
			break;
		case GLFW_KEY_Y:
			mBufButtons |= Y;
			break;
		case GLFW_KEY_Z:
			mBufButtons |= Z;
			break;
		case GLFW_KEY_UP:
			mBufButtons |= UP;
			break;
		case GLFW_KEY_DOWN:
			mBufButtons |= DOWN;
			break;
		case GLFW_KEY_LEFT:
			mBufButtons |= LEFT;
			break;
		case GLFW_KEY_RIGHT:
			mBufButtons |= RIGHT;
			break;
		case GLFW_KEY_LEFT_SHIFT:
			mBufButtons |= LEFT_SHIFT;
			break;
		case GLFW_KEY_LEFT_CONTROL:
			mBufButtons |= LEFT_CTRL;
			break;
		default:
			break;
		}
	}

	else if (action == GLFW_RELEASE) {
		switch (key) {
		case GLFW_KEY_A:
			mBufButtons &= ~A;
			break;
		case GLFW_KEY_B:
			mBufButtons &= ~B;
			break;
		case GLFW_KEY_C:
			mBufButtons &= ~C;
			break;
		case GLFW_KEY_D:
			mBufButtons &= ~D;
			break;
		case GLFW_KEY_E:
			mBufButtons &= ~E;
			break;
		case GLFW_KEY_F:
			mBufButtons &= ~F;
			break;
		case GLFW_KEY_G:
			mBufButtons &= ~G;
			break;
		case GLFW_KEY_H:
			mBufButtons &= ~H;
			break;
		case GLFW_KEY_I:
			mBufButtons &= ~I;
			break;
		case GLFW_KEY_J:
			mBufButtons &= ~J;
			break;
		case GLFW_KEY_K:
			mBufButtons &= ~K;
			break;
		case GLFW_KEY_L:
			mBufButtons &= ~L;
			break;
		case GLFW_KEY_M:
			mBufButtons &= ~M;
			break;
		case GLFW_KEY_N:
			mBufButtons &= ~N;
			break;
		case GLFW_KEY_O:
			mBufButtons &= ~O;
			break;
		case GLFW_KEY_P:
			mBufButtons &= ~P;
			break;
		case GLFW_KEY_Q:
			mBufButtons &= ~Q;
			break;
		case GLFW_KEY_R:
			mBufButtons &= ~R;
			break;
		case GLFW_KEY_S:
			mBufButtons &= ~S;
			break;
		case GLFW_KEY_T:
			mBufButtons &= ~T;
			break;
		case GLFW_KEY_U:
			mBufButtons &= ~U;
			break;
		case GLFW_KEY_V:
			mBufButtons &= ~V;
			break;
		case GLFW_KEY_W:
			mBufButtons &= ~W;
			break;
		case GLFW_KEY_X:
			mBufButtons &= ~X;
			break;
		case GLFW_KEY_Y:
			mBufButtons &= ~Y;
			break;
		case GLFW_KEY_Z:
			mBufButtons &= ~Z;
			break;
		case GLFW_KEY_UP:
			mBufButtons &= ~UP;
			break;
		case GLFW_KEY_DOWN:
			mBufButtons &= ~DOWN;
			break;
		case GLFW_KEY_LEFT:
			mBufButtons &= ~LEFT;
			break;
		case GLFW_KEY_RIGHT:
			mBufButtons &= ~RIGHT;
			break;
		case GLFW_KEY_LEFT_SHIFT:
			mBufButtons &= ~LEFT_SHIFT;
			break;
		case GLFW_KEY_LEFT_CONTROL:
			mBufButtons &= ~LEFT_CTRL;
		default:
			break;
		}
	}
}

void KeyMouseInputService::MouseButtonCallback(GLFWwindow* pWindow, int button, int action, int mods) {
	if (mPrevMouseButtonCallback != nullptr) {
		mPrevMouseButtonCallback(pWindow, button, action, mods);
	}
	
	if (action == GLFW_PRESS) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT:
			mBufButtons |= LEFT_MOUSE_BUTTON;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			mBufButtons |= MIDDLE_MOUSE_BUTTON;
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			mBufButtons |= RIGHT_MOUSE_BUTTON;
			break;
		default:
			break;
		}
	}

	else if (action == GLFW_RELEASE) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_LEFT:
			mBufButtons &= ~LEFT_MOUSE_BUTTON;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			mBufButtons &= ~MIDDLE_MOUSE_BUTTON;
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			mBufButtons &= ~RIGHT_MOUSE_BUTTON;
			break;
		default:
			break;
		}
	}
}

void KeyMouseInputService::CursorPosCallback(GLFWwindow* pWindow, double xpos, double ypos) {
	if (mPrevCursorPosCallback != nullptr) {
		mPrevCursorPosCallback(pWindow, xpos, ypos);
	}
	
	mBufXMousePos = xpos;
	mBufYMousePos = ypos;
}

void KeyMouseInputService::Startup() {
	glfwSetWindowUserPointer(InputManager::Instance().Window(), this);

	mPrevKeyCallback = glfwSetKeyCallback(InputManager::Instance().Window(), KeyMouseInputService::KeyCallbackForwarder);

	mPrevMouseButtonCallback = glfwSetMouseButtonCallback(InputManager::Instance().Window(), KeyMouseInputService::MouseButtonCallbackForwarder);

	mPrevCursorPosCallback = glfwSetCursorPosCallback(InputManager::Instance().Window(), KeyMouseInputService::CursorPosCallbackForwarder);
}

void KeyMouseInputService::KeyCallbackForwarder(GLFWwindow* pWindow, int key, int scancode, int action, int mods) {
	KeyMouseInputService* pService = static_cast<KeyMouseInputService*>(glfwGetWindowUserPointer(pWindow));

	pService->KeyCallback(pWindow, key, scancode, action, mods);
}

void KeyMouseInputService::MouseButtonCallbackForwarder(GLFWwindow* pWindow, int button, int action, int mods) {
	KeyMouseInputService* pService = static_cast<KeyMouseInputService*>(glfwGetWindowUserPointer(pWindow));

	pService->MouseButtonCallback(pWindow, button, action, mods);
}

void KeyMouseInputService::CursorPosCallbackForwarder(GLFWwindow* pWindow, double xpos, double ypos) {
	KeyMouseInputService* pService = static_cast<KeyMouseInputService*>(glfwGetWindowUserPointer(pWindow));
	pService->CursorPosCallback(pWindow, xpos, ypos);
}

#else // not GLFW3

void KeyMouseInputService::poll_events() { }
#endif // end platform-/framework-specific