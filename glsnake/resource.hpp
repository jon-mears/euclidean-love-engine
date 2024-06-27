#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <string>

class Resource {
protected:
	std::string mName;
public:

	virtual ~Resource() = 0;
	Resource(const std::string& name);
	Resource();

	std::string &name();
	void set_name(const std::string& name);
};

#endif