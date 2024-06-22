#ifndef XMLPARSER_HPP
#define XMLPARSER_HPP

#include <string>

class XMLTree;
class XMLState;

class XMLParser {
private:
	XMLState* mpState;
	char mChar;
public:
	XMLTree *read(std::string filename);
};
#endif