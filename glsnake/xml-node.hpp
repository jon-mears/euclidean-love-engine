#ifndef XML_NODE_HPP
#define XML_NODE_HPP

#include <string>
#include <map>
#include <vector>

class XMLNode {
private:
	std::vector<XMLNode*> mChildren;
	std::string mTag;
	std::string mContent;
	std::map<std::string, std::string> mAttributes;
public:
	void AddChild(XMLNode* pChild);
	void AddAttrib(const std::string& name, const std::string& value);
	void AddContent(const std::string& content);
	void AddTag(const std::string& tag);

	XMLNode* operator[](size_t idx) const;
	XMLNode* Child(size_t idx) const;
	size_t NumChildren() const;
	bool Has(const std::string& attrib);

	std::string Content();
	std::string Attribute(const std::string& name);
	std::string Tag() const;
};
#endif