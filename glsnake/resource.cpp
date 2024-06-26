#include "resource.hpp"

Resource::Resource(const std::string& name) : mName(name) { }
Resource::Resource() : mName("") { }

std::string &Resource::name() {
	return mName;
}

void Resource::set_name(const std::string& name) {
	mName = name;
}

Resource::~Resource() { }