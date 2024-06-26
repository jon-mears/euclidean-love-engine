#ifndef XMLTREE_HPP
#define XMLTREE_HPP

class XMLNode;

class XMLTree {
private:
	XMLNode* mRoot;
public:
	XMLNode* root();

	friend class XMLParser;
};
#endif