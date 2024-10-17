#ifndef XML_TREE_HPP
#define XML_TREE_HPP

class XMLNode;

class XMLTree {
private:
	XMLNode* mpRoot;
public:
	XMLNode* Root();

	friend class XMLParser;
};
#endif