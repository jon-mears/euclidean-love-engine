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
	virtual float absolute_axis(Input::Axis axis) = 0;
	virtual float relative_axis(Input::Axis axis) = 0;
	virtual bool event_active(Input::Event event) = 0;
	virtual void poll_events() = 0;

	virtual void startup() = 0;
};
#endif