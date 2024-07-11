#include "xml-state.hpp"
#include "xml-parser.hpp"
#include "xml-tree.hpp"
#include "xml-node.hpp"

#include <string>
#include <utility>
#include <iostream>

// XMLState

XMLState::~XMLState() { }

StateCommand XMLState::Enter(XMLParser& rParser) {
	return StateCommand(StateAction::NIL, nullptr);
}

StateCommand XMLState::Exit(XMLParser& rParser) {
	return StateCommand(StateAction::NIL, nullptr);
}

// XMLBegin

StateCommand XMLBegin::Enter(XMLParser& rParser) {
	return StateCommand(StateAction::PUSH, new XMLWhitespace());
}

StateCommand XMLBegin::Process(XMLParser& rParser) {
	if (rParser.mChar != '<') {
		std::cerr << "xml file must begin with a tag!" << std::endl;
		std::exit(-1);

		return StateCommand(StateAction::NIL, nullptr);
	}

	else {
		return StateCommand(StateAction::REPLACE, new XMLTag());
	}
}

StateCommand XMLBegin::Exit(XMLParser& rParser) {
	return StateCommand(StateAction::NIL, nullptr);
}

// XMLTag

StateCommand XMLTag::Enter(XMLParser& rParser) {
	return StateCommand(StateAction::PUSH, new XMLWhitespace());
}

StateCommand XMLTag::Process(XMLParser& rParser) {
	if (rParser.mChar == '/') {
		return StateCommand(StateAction::REPLACE, new XMLEndTagname());
	}

	else {
		rParser.mFile.unget();
		return StateCommand(StateAction::REPLACE, new XMLBeginTagname());
	}
}

// XMLBeginTagname

StateCommand XMLBeginTagname::Process(XMLParser& rParser) {
	if (std::isalnum(rParser.mChar)) {
		mTagname[mIndex++] = rParser.mChar;
	}

	else if (std::isspace(rParser.mChar)) {
		return StateCommand(StateAction::REPLACE, new XMLAttribName());
	}

	else if (rParser.mChar == '>') {
		return StateCommand(StateAction::REPLACE, new XMLContent());
	}

	else if (rParser.mChar == '/') {
		return StateCommand(StateAction::REPLACE, new XMLTagCloser());
	}

	return StateCommand(StateAction::NIL, nullptr);
}

StateCommand XMLBeginTagname::Exit(XMLParser& rParser) {
	XMLNode* pNewNode = new XMLNode();
	mTagname[mIndex] = '\0';
	pNewNode->AddTag(std::string(mTagname));

	rParser.AddNode(pNewNode);

	return StateCommand(StateAction::NIL, nullptr);
}

// XMLEndTagname

StateCommand XMLEndTagname::Enter(XMLParser& rParser) {
	return StateCommand(StateAction::PUSH, new XMLWhitespace());
}

StateCommand XMLEndTagname::Process(XMLParser& rParser) {
	if (std::isalnum(rParser.mChar)) {
		mTagname[mIndex++] = rParser.mChar;
	}

	else if (rParser.mChar == '>') {
		return StateCommand(StateAction::POP, nullptr);
	}

	else if (isspace(rParser.mChar)) {
		return StateCommand(StateAction::REPLACE, new XMLTagCloser());
	}

	return StateCommand(StateAction::NIL, nullptr);
}

StateCommand XMLEndTagname::Exit(XMLParser& rParser) {
	mTagname[mIndex] = '\0';
	std::string s(mTagname);

	if (s != rParser.mNodes.top()->Tag()) {
		std::cerr << "tag " << rParser.mNodes.top()->Tag() << " is unmatched!" << std::endl;
		std::exit(-1);
	}

	// get rid of the Content state
	return StateCommand(StateAction::POP, nullptr);
}

// XMLTagCloser

StateCommand XMLTagCloser::Enter(XMLParser& rParser) {
	return StateCommand(StateAction::PUSH, new XMLWhitespace());
}

StateCommand XMLTagCloser::Process(XMLParser& rParser) {
	if (rParser.mChar != '>') {
		std::cerr << "error detected in xml closer!" << std::endl;
		std::exit(-1);
	}

	return StateCommand(StateAction::POP, nullptr);
}

// XMLAttribName

StateCommand XMLAttribName::Enter(XMLParser& rParser) {
	return StateCommand(StateAction::PUSH, new XMLWhitespace());
}

StateCommand XMLAttribName::Process(XMLParser& rParser) {
	if (std::isalnum(rParser.mChar)) {
		mAttribName[mIndex++] = rParser.mChar;
	}

	else if (rParser.mChar == '>') {
		return StateCommand(StateAction::REPLACE, new XMLContent());
	}

	else if (rParser.mChar == '/') {
		return StateCommand(StateAction::REPLACE, new XMLTagCloser());
	}

	else if (isspace(rParser.mChar)) {
		mAttribName[mIndex] = '\0';
		return StateCommand(StateAction::REPLACE, new XMLAttribNameCloser(mAttribName));
	}

	else if (rParser.mChar = '=') {
		mAttribName[mIndex] = '\0';
		return StateCommand(StateAction::REPLACE, new XMLAttribValue(mAttribName));
	}

	return StateCommand(StateAction::NIL, nullptr);
}

// XMLAttribNameCloser

XMLAttribNameCloser::XMLAttribNameCloser(char* pAttribName) : mAttribName{pAttribName} { }

StateCommand XMLAttribNameCloser::Process(XMLParser& rParser) {
	if (rParser.mChar == '=') {
		return StateCommand(StateAction::REPLACE, new XMLAttribValue(mAttribName));
	}
	
	else if (rParser.mChar == '/') {
		rParser.mNodes.top()->AddAttrib(mAttribName, "");
		return StateCommand(StateAction::REPLACE, new XMLTagCloser());
	}

	else if (std::isalnum(rParser.mChar)) {
		rParser.mNodes.top()->AddAttrib(mAttribName, "");
		return StateCommand(StateAction::REPLACE, new XMLAttribName());
	}

	return StateCommand(StateAction::NIL, nullptr);
}

// XMLAttribValue

XMLAttribValue::XMLAttribValue(char* attrib_name) : mAttribName(attrib_name), mAttribValue(), mIndex(0) { }

XMLAttribValue::XMLAttribValue(const std::string& attrib_name) : mAttribName(attrib_name), mAttribValue(), mIndex(0) { }

StateCommand XMLAttribValue::Enter(XMLParser& rParser) {
	return StateCommand(StateAction::PUSH, new XMLWhitespace());
}

StateCommand XMLAttribValue::Process(XMLParser& rParser) {
	if (mIndex == 0 && rParser.mChar != '"') {
		std::cerr << "attribute values must be quoted!" << std::endl;
		std::exit(-1);
	}

	else if (mIndex != 0 && rParser.mChar == '"') {
		return StateCommand(StateAction::REPLACE, new XMLAttribName());
	}

	else {
		mAttribValue[mIndex++] = rParser.mChar;

		return StateCommand(StateAction::NIL, nullptr);
	}
}

StateCommand XMLAttribValue::Exit(XMLParser& rParser) {
	mAttribValue[mIndex] = '\0';
	std::string attrib_value(mAttribValue);

	// remove the open quote (could instead use a counter for each state perhaps)
	attrib_value = attrib_value.substr(1);

	rParser.mNodes.top()->AddAttrib(mAttribName, attrib_value);
	return StateCommand(StateAction::NIL, nullptr);
}

// XMLContent

StateCommand XMLContent::Process(XMLParser& rParser) {
	if (rParser.mChar == '<') {
		return StateCommand(StateAction::PUSH, new XMLTag());
	}

	else {
		mContent[mIndex++] = rParser.mChar;
		return StateCommand(StateAction::NIL, nullptr);
	}
}

StateCommand XMLContent::Exit(XMLParser& rParser) {
	mContent[mIndex] = '\0';
	std::string s(mContent);

	rParser.mNodes.top()->AddContent(s);

	rParser.mNodes.pop();
	return StateCommand(StateAction::NIL, nullptr);
}

// XMLWhitespace

StateCommand XMLWhitespace::Process(XMLParser& rParser) {
	if (!isspace(rParser.mChar)) {
		rParser.mFile.unget();
		return StateCommand(StateAction::POP, nullptr);
	}

	return StateCommand(StateAction::NIL, nullptr);
}