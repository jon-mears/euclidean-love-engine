#include "subject.hpp" 
#include "observer.hpp"

#include <vector>

void Subject::notify(Event e) {
	for (Observer* o : observers) {
		o->on_notify(e);
	}
}

void Subject::register_observer(Observer* o) {
	observers.push_back(o);
}

void Subject::remove_observer(Observer* o) {
	for (std::vector<Observer*>::iterator it = observers.begin(); it != observers.end(); ++it) {
		if (*it == o) {
			observers.erase(it);
		}
	}
}