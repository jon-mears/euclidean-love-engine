#ifndef OBSERVER_HPP
#define OBSERVER_HPP

enum class Event;

class Observer {
public:
	virtual ~Observer() { }
	virtual void on_notify(Event e) = 0;
};
#endif