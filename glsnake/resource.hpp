#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <string>

class Resource {
private:
	std::string mName;
public:

	virtual ~Resource();
	Resource(const std::string& name);
	Resource();

	std::string &name();
	void set_name(const std::string& name);
};

#endif