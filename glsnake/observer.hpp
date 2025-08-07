#ifndef OBSERVER_HPP
#define OBSERVER_HPP

enum class Event {
	WINDOW_RESIZE
};

class Observer {
public:
	virtual ~Observer() { }
	virtual void OnNotify(Event event, void* data) = 0;
};


#endif