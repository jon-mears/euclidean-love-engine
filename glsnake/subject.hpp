#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include <vector>

#include "observer.hpp"

class Subject {
private:
	std::vector<Observer*> mObservers;
public:
	inline void AddObserver(Observer* pObserver) {
		mObservers.push_back(pObserver);
	}

};
#endif