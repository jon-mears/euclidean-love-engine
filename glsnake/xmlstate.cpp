#include "xmlstate.hpp"
#include "xmlparser.hpp"
#include "xmltree.hpp"
#include "xmlnode.hpp"

#include <string>
#include <utility>
#include <iostream>

// XMLState

XMLState::~XMLState() { }

StateCommand XMLState::enter(XMLParser& parser) {
	return StateCommand(StateAction::NIL, NULL);
}

StateCommand XMLState::exit(XMLParser& parser) {
	return StateCommand(StateAction::NIL, NULL);
}

// XMLBegin

StateCommand XMLBegin::enter(XMLParser& parser) {
	return StateCommand(StateAction::PUSH, new XMLWhitespace());
}

StateCommand XMLBegin::process(XMLParser& parser) {
	if (parser.mChar != '<') {
		std::cout << "xml file must begin with a tag!" << std::endl;
		std::exit(-1);

		return StateCommand(StateAction::NIL, NULL);
	}

	else {
		return StateCommand(StateAction::REPLACE, new XMLTag());
	}
}

StateCommand XMLBegin::exit(XMLParser& parser) {
	return StateCommand(StateAction::NIL, NULL);
}

// XMLTag

StateCommand XMLTag::enter(XMLParser& parser) {
	return StateCommand(StateAction::PUSH, new XMLWhitespace());
}

StateCommand XMLTag::process(XMLParser& parser) {
	if (parser.mChar == '/') {
		return StateCommand(StateAction::REPLACE, new XMLEndTagname());
	}

	else {
		parser.mFile.unget();
		return StateCommand(StateAction::REPLACE, new XMLBeginTagname());
	}
}

// XMLBeginTagname

StateCommand XMLBeginTagname::process(XMLParser& parser) {
	if (std::isalpha(parser.mChar)) {
		mTagname[mIndex++] = parser.mChar;
	}

	else if (std::isspace(parser.mChar)) {
		return StateCommand(StateAction::REPLACE, new XMLAttribName());
	}

	else if (parser.mChar == '>') {
		return StateCommand(StateAction::REPLACE, new XMLContent());
	}

	else if (parser.mChar == '/') {
		return StateCommand(StateAction::REPLACE, new XMLTagCloser());
	}

	return StateCommand(StateAction::NIL, NULL);
}

StateCommand XMLBeginTagname::exit(XMLParser& parser) {
	XMLNode* new_node = new XMLNode();
	mTagname[mIndex] = '\0';
	new_node->add_tag(std::string(mTagname));

	parser.add_node(new_node);

	return StateCommand(StateAction::NIL, NULL);
}

// XMLEndTagname

StateCommand XMLEndTagname::enter(XMLParser& parser) {
	return StateCommand(StateAction::PUSH, new XMLWhitespace());
}

StateCommand XMLEndTagname::process(XMLParser& parser) {
	if (isalpha(parser.mChar)) {
		mTagname[mIndex++] = parser.mChar;
	}

	else if (parser.mChar == '>') {
		return StateCommand(StateAction::POP, NULL);
	}

	else if (isspace(parser.mChar)) {
		return StateCommand(StateAction::REPLACE, new XMLTagCloser());
	}

	return StateCommand(StateAction::NIL, NULL);
}

StateCommand XMLEndTagname::exit(XMLParser& parser) {
	mTagname[mIndex] = '\0';
	std::string s(mTagname);

	if (s != parser.mNodes.top()->tag()) {
		std::cout << "tag " << parser.mNodes.top()->tag() << " is unmatched!" << std::endl;
		std::exit(-1);
	}

	//else {
	//	parser.mNodes.pop();
	//}

	// get rid of the Content state
	return StateCommand(StateAction::POP, NULL);
}

// XMLTagCloser

StateCommand XMLTagCloser::enter(XMLParser& parser) {
	return StateCommand(StateAction::PUSH, new XMLWhitespace());
}

StateCommand XMLTagCloser::process(XMLParser& parser) {
	if (parser.mChar != '>') {
		std::cout << "error detected in xml closer!" << std::endl;
		std::exit(-1);
	}

	return StateCommand(StateAction::POP, NULL);
}

// XMLAttribName

StateCommand XMLAttribName::enter(XMLParser& parser) {
	return StateCommand(StateAction::PUSH, new XMLWhitespace());
}

StateCommand XMLAttribName::process(XMLParser& parser) {
	if (isalpha(parser.mChar)) {
		mAttribName[mIndex++] = parser.mChar;
	}

	else if (parser.mChar == '>') {
		return StateCommand(StateAction::REPLACE, new XMLContent());
	}

	else if (parser.mChar == '/') {
		return StateCommand(StateAction::REPLACE, new XMLTagCloser());
	}

	else if (isspace(parser.mChar)) {
		mAttribName[mIndex] = '\0';
		return StateCommand(StateAction::REPLACE, new XMLAttribNameCloser(mAttribName));
	}

	else if (parser.mChar = '=') {
		mAttribName[mIndex] = '\0';
		return StateCommand(StateAction::REPLACE, new XMLAttribValue(mAttribName));
	}

	return StateCommand(StateAction::NIL, NULL);
}

// XMLAttribNameCloser

XMLAttribNameCloser::XMLAttribNameCloser(char* attrib_name) : mAttribName(attrib_name) { }

StateCommand XMLAttribNameCloser::process(XMLParser& parser) {
	if (parser.mChar == '=') {
		return StateCommand(StateAction::REPLACE, new XMLAttribValue(mAttribName));
	}
	
	else if (parser.mChar == '/') {
		parser.mNodes.top()->add_attrib(mAttribName, "");
		return StateCommand(StateAction::REPLACE, new XMLTagCloser());
	}

	else if (isalpha(parser.mChar)) {
		parser.mNodes.top()->add_attrib(mAttribName, "");
		return StateCommand(StateAction::REPLACE, new XMLAttribName());
	}

	return StateCommand(StateAction::NIL, NULL);
}

// XMLAttribValue

XMLAttribValue::XMLAttribValue(char* attrib_name) : mAttribName(attrib_name), mAttribValue(), mIndex(0) { }

XMLAttribValue::XMLAttribValue(const std::string& attrib_name) : mAttribName(attrib_name), mAttribValue(), mIndex(0) { }

StateCommand XMLAttribValue::enter(XMLParser& parser) {
	return StateCommand(StateAction::PUSH, new XMLWhitespace());
}

StateCommand XMLAttribValue::process(XMLParser& parser) {
	if (mIndex == 0 && parser.mChar != '"') {
		std::cout << "attribute values must be quoted!" << std::endl;
		std::exit(-1);
	}

	else if (mIndex != 0 && parser.mChar == '"') {
		return StateCommand(StateAction::REPLACE, new XMLAttribName());
	}

	else {
		mAttribValue[mIndex++] = parser.mChar;

		return StateCommand(StateAction::NIL, NULL);
	}
}

StateCommand XMLAttribValue::exit(XMLParser& parser) {
	mAttribValue[mIndex] = '\0';
	std::string attrib_value(mAttribValue);

	// remove the open quote (could instead use a counter for each state perhaps)
	attrib_value = attrib_value.substr(1);

	parser.mNodes.top()->add_attrib(mAttribName, attrib_value);
	return StateCommand(StateAction::NIL, NULL);
}

// XMLContent

StateCommand XMLContent::process(XMLParser& parser) {
	if (parser.mChar == '<') {
		return StateCommand(StateAction::PUSH, new XMLTag());
	}

	else {
		mContent[mIndex++] = parser.mChar;
		return StateCommand(StateAction::NIL, NULL);
	}
}

StateCommand XMLContent::exit(XMLParser& parser) {
	mContent[mIndex] = '\0';
	std::string s(mContent);

	parser.mNodes.top()->add_content(s);

	parser.mNodes.pop();
	return StateCommand(StateAction::NIL, NULL);
}

// XMLWhitespace

StateCommand XMLWhitespace::process(XMLParser& parser) {
	if (!isspace(parser.mChar)) {
		parser.mFile.unget();
		return StateCommand(StateAction::POP, NULL);
	}

	return StateCommand(StateAction::NIL, NULL);
}