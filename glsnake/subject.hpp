#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include <vector>

enum class Event {
	W_DOWN,
	A_DOWN,
	S_DOWN,
	D_DOWN
};

class Observer;
class Subject {

private:
	std::vector<Observer*> observers;
public:
	void notify(Event e);
	void register_observer(Observer* o);
	void remove_observer(Observer* o);
};
#endif