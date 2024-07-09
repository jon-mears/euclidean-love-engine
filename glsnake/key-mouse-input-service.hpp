#ifndef KEY_MOUSE_INPUT_SERVICE_HPP
#define KEY_MOUSE_INPUT_SERVICE_HPP

#include "input-service.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#ifdef _glfw3_h_
class GLFWwindow;
typedef GLFWkeyfun KeyCallback;
typedef GLFWmousebuttonfun MouseButtonCallback;
typedef GLFWcursorposfun CursorPosCallback;
#endif

class KeyMouseInputService : public InputService {
private:
	unsigned long mBufButtons, mButtons, mPrevButtons;
	double mBufXMousePos, mBufYMousePos, mXMousePos, mYMousePos, mPrevXMousePos, mPrevYMousePos;
	unsigned long mButtonUps;
	unsigned long mButtonDowns;

	KeyCallback mPrevKeyCallback = nullptr;
	MouseButtonCallback mPrevMouseButtonCallback = nullptr;
	CursorPosCallback mPrevCursorPosCallback = nullptr;

	bool IsDown(unsigned long include, unsigned long exclude=0); // can also be used for chords
	bool Pressed(unsigned long include, unsigned long exclude=0); // can also be used for chords
	bool Released(unsigned long include, unsigned long exclude=0); // can also be used for chords

#ifdef _glfw3_h_
	void KeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mods);
	static void KeyCallbackForwarder(GLFWwindow* pWindow, int key, int scancode, int action, int mods);

	void MouseButtonCallback(GLFWwindow* pWindow, int button, int action, int mods);
	static void MouseButtonCallbackForwarder(GLFWwindow* pWindow, int button, int action, int mods);

	void CursorPosCallback(GLFWwindow* pWindow, double xpos, double ypos);
	static void CursorPosCallbackForwarder(GLFWwindow* pWindow, double xpos, double ypos);
#endif

public:
	virtual float AbsoluteAxis(Input::Axis eAxis) override;
	virtual float RelativeAxis(Input::Axis eAxis) override;
	virtual bool EventActive(Input::Event eEvent) override;
	virtual void PollEvents() override;
	virtual void Startup() override;
};

#endif