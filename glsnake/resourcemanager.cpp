#include "resourcemanager.hpp"
#include <fstream>
#include <iostream>

void ResourceManager::startup() {
	XMLParser* pParser = new XMLParser();
	XMLTree* pTree = pParser->read("C:\\assets\\resources.xml");
}