#include "xml-node.hpp"

void XMLNode::AddChild(XMLNode* pChild) {
	mChildren.push_back(pChild);
}

void XMLNode::AddAttrib(const std::string& name, const std::string& value) {
	mAttributes[name] = value;
}

void XMLNode::AddContent(const std::string& content) {
	mContent = content;
}

void XMLNode::AddTag(const std::string& tag) {
	mTag = tag;
}

XMLNode* XMLNode::operator[](size_t idx) const {
	return mChildren[idx];
}

XMLNode* XMLNode::Child(size_t idx) const {
	return mChildren[idx];
}

size_t XMLNode::NumChildren() const {
	return mChildren.size();
}

bool XMLNode::Has(const std::string& name) {
	return mAttributes.count(name);
}

std::string XMLNode::Attribute(const std::string& name) {
	return mAttributes[name];
}

std::string XMLNode::Tag() const {
	return mTag;
}

std::string XMLNode::Content() {
	return mContent;
}