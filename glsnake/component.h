#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
public:
	virtual ~Component();

	virtual void start() = 0;
	virtual void update() = 0;
};

#endif