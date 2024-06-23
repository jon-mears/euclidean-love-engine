#include "xmlstate.hpp"
#include "xmlparser.hpp"
#include "xmltree.hpp"
#include "xmlnode.hpp"

#include <string>
#include <utility>
#include <iostream>

XMLState::~XMLState() { }

StateCommand XMLState::enter(XMLParser& parser) {
	return StateCommand(StateAction::NIL, NULL);
}

StateCommand XMLState::exit(XMLParser& parser) {
	return StateCommand(StateAction::NIL, NULL);
}

StateCommand XMLBegin::enter(XMLParser& parser) {
	return StateCommand(StateAction::PUSH, new XMLWhitespace());
}

StateCommand XMLBegin::process(XMLParser& parser) {
	if (parser.mChar != '<') {
		std::cout << "xml file must begin w/ a tag!" << std::endl;
		std::exit(-1);
	}

	else {
		return StateCommand(StateAction::REPLACE, new XMLTagname());
	}
}

StateCommand XMLTag::enter(XMLParser& parser) {
	return StateCommand(StateAction::REPLACE, new XMLWhitespace());
}

StateCommand XMLTag::process(XMLParser& parser) {

}

StateCommand XMLBegin::exit(XMLParser& parser) {
	XMLNode* root = new XMLNode();
	parser.mNodes.push(root);

	return StateCommand(StateAction::NIL, NULL);
}

StateCommand XMLTagname::process(XMLParser& parser) {
	if (std::isalpha(parser.mChar)) {
		mTagname[mIndex++] = parser.mChar;
	}

	else if (std::isspace(parser.mChar)) {
		return StateCommand(StateAction::PUSH, new XMLAttribName());
	}

	else if (parser.mChar == '>') {
		return StateCommand(StateAction::REPLACE, new XMLContent());
	}

	else if (mIndex != 0 && parser.mChar == '/') {
		return StateCommand(StateAction::REPLACE, new XMLTagCloser());
	}

	else if (mIndex == 0 && parser.mChar == '/') {
		return StateCommand()
	}

	return StateCommand(StateAction::NIL, NULL);
}

StateCommand XMLTagname::exit(XMLParser& parser) {
	mTagname[mIndex] = '\0';
	parser.mNodes.top()->add_tag(std::string(mTagname));
}

StateCommand XMLTagname::enter(XMLParser& parser) {
	return StateCommand(StateAction::PUSH, new XMLWhitespace());
}

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
}

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
}

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
	}
}

StateCommand XMLAttribValue::exit(XMLParser& parser) {
	mAttribValue[mIndex] = '\0';
	std::string attrib_value(mAttribValue);

	parser.mNodes.top()->add_attrib(mAttribName, attrib_value);
	return StateCommand(StateAction::NIL, NULL);
}

StateCommand XMLContent::process(XMLParser& parser) {

}

StateCommand XMLWhitespace::process(XMLParser& parser) {
	if (!isspace(parser.mChar)) {
		parser.mFile.unget();
		return StateCommand(StateAction::POP, NULL);
	}

	return StateCommand(StateAction::NIL, NULL);
}