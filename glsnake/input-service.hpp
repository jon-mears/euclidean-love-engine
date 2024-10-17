#ifndef INPUT_SERVICE_HPP
#define INPUT_SERVICE_HPP

namespace Input {
	enum Event;
	enum Axis;
}

class InputService {

public:
	virtual ~InputService() { }

	// interface
	virtual float AbsoluteAxis(Input::Axis eAxis) = 0;
	virtual float RelativeAxis(Input::Axis eAxis) = 0;
	virtual bool EventActive(Input::Event eEvent) = 0;
	virtual void PollEvents() = 0;

	virtual void Startup() = 0;
};
#endif