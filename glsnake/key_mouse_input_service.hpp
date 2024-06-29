#ifndef KEY_MOUSE_INPUT_SERVICE_HPP
#define KEY_MOUSE_INPUT_SERVICE_HPP

#include "InputService.hpp"
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
	unsigned long mBButtons, mButtons, mPrevButtons;
	double mBXMousePos, mBYMousePos, mXMousePos, mYMousePos, mPrevXMousePos, mPrevYMousePos;
	unsigned long mButtonUps;
	unsigned long mButtonDowns;

	KeyCallback mPrevKeyCallback = NULL;
	MouseButtonCallback mPrevMouseButtonCallback = NULL;
	CursorPosCallback mPrevCursorPosCallback = NULL;

	bool is_down(unsigned long buttons); // can also be used for chords
	bool pressed(unsigned long buttons); // can also be used for chords
	bool released(unsigned long buttons); // can also be used for chords

#ifdef _glfw3_h_
	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void key_callback_forwarder(GLFWwindow* window, int key, int scancode, int action, int mods);

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static void mouse_button_callback_forwarder(GLFWwindow* window, int button, int action, int mods);

	void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
	static void cursor_pos_callback_forwarder(GLFWwindow* window, double xpos, double ypos);
#endif

public:
	virtual float absolute_axis(Input::Axis axis) override;
	virtual float relative_axis(Input::Axis axis) override;
	virtual bool event_active(Input::Event event) override;
	virtual void poll_events() override;
	virtual void startup() override;
};

#endif