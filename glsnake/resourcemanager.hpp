#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <vector>

class Game;

class ResourceManager {
private:
	ResourceManager();
	void startup();
public:
	friend class Game;
};
#endif