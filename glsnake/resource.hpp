#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include <string>

class Resource {
protected:
	std::string mName;
public:
	Resource(const std::string& name);
	Resource();

	inline const std::string& Name() { return mName; }

	friend class ResourceManager;
};

#endif