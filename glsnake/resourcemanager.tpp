#ifndef RESOURCEMANAGER_TPP
#define RESOURCEMANAGER_TPP

#include "resourcemanager.hpp"
#include <string>

template <typename T>
T* ResourceManager::retrieve(const std::string name) {
	return dynamic_cast<T*>(mResources[name]);
}
#endif