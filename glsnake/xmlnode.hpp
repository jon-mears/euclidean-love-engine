#ifndef XMLNODE_HPP
#define XMLNODE_HPP

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
	void add_child(XMLNode* child);
	void add_attrib(const std::string& name, const std::string& value);
	void add_content(const std::string& content);
	void add_tag(const std::string& tag);

	XMLNode* operator[](size_t idx) const;
	XMLNode* child(size_t idx) const;
	size_t num_children() const;
	bool has(const std::string& attrib);

	std::string content();
	std::string attribute(const std::string& name);
	std::string tag() const;
};
#endif