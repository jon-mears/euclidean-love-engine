#ifndef XMLTREE_HPP
#define XMLTREE_HPP

class XMLNode;

class XMLTree {
private:
	XMLNode* mRoot;
public:
	XMLNode* root();

	friend class XMLBegin;
	friend class XMLTagname;
	friend class XMLAttribute;
	friend class XMLContent;
};
#endif