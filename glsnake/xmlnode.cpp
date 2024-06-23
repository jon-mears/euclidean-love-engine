#include "xmlnode.hpp"

void XMLNode::add_child(XMLNode* child) {
	mChildren.push_back(child);
}

void XMLNode::add_attrib(const std::string& name, const std::string& value) {
	mAttributes[name] = value;
}

void XMLNode::add_content(const std::string& content) {
	mContent = content;
}

void XMLNode::add_tag(const std::string& tag) {
	mTag = tag;
}

XMLNode* XMLNode::operator[](size_t idx) const {
	return mChildren[idx];
}

size_t XMLNode::num_children() const {
	return mChildren.size();
}

bool XMLNode::has(const std::string& name) {
	return mAttributes.count(name);
}

std::string XMLNode::attribute(const std::string& name) {
	return mAttributes[name];
}

std::string XMLNode::tag() const {
	return mTag;
}