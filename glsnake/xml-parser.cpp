#include "xml-parser.hpp"
#include "xml-tree.hpp"
#include "xml-state.hpp"
#include "xml-node.hpp"

#include <fstream>
#include <iostream>

XMLParser::XMLParser() : mpTree{ nullptr }, mNodes{}, mStates{}, mFile{}, mChar{} { }

XMLTree* XMLParser::Parse(const std::string& filename) {
	mpTree = new XMLTree();

	XMLState* pBeginState = new XMLBegin();
	mStates.push(pBeginState);

	HandleEnter(pBeginState);

	mFile.open(filename);

	if (!mFile.is_open()) {
		std::cerr << "could not open the file " << filename << std::endl;
		std::exit(-1);
	}

	while ((mChar = mFile.get()) && !mStates.empty()) {
		StateCommand command = mStates.top()->Process(*this);
		ProcessCommand(command);
	}

	mFile.close();

	if (!mNodes.empty()) {
		std::cerr << "not all tags were closed!" << std::endl;
		std::exit(-1);
	}

	return mpTree;
}

void XMLParser::Reset() {
	mpTree = nullptr;
}

void XMLParser::HandleEnter(XMLState* pState) {
	StateCommand command = pState->Enter(*this);
	ProcessCommand(command);
}

void XMLParser::HandleExit(XMLState* pState) {
	StateCommand command = pState->Exit(*this);
	ProcessCommand(command);
	delete pState;
}

void XMLParser::ProcessCommand(const StateCommand& rcCommand) {
	StateAction action = rcCommand.first;
	XMLState* pState = rcCommand.second;

	switch (action) {
	case StateAction::POP:
	{
		XMLState* pTopState = mStates.top();
		mStates.pop();

		HandleExit(pTopState);
		break;
	}
	case StateAction::PUSH:
		mStates.push(pState);

		HandleEnter(pState);
		break;
	case StateAction::REPLACE:
	{
		XMLState* pTopState = mStates.top();
		mStates.pop();

		HandleExit(pTopState);

		mStates.push(pState);

		HandleEnter(pState);
		break;
	}
	case StateAction::NIL:
		break;
	default:
		break;
	}
}

void XMLParser::AddNode(XMLNode* pNode) {
	if (mNodes.empty()) {
		mpTree->mpRoot = pNode;
	}

	else {
		mNodes.top()->AddChild(pNode);
	}

	mNodes.push(pNode);
}