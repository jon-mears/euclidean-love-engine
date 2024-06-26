#include "xmlparser.hpp"
#include "xmltree.hpp"
#include "xmlstate.hpp"
#include "xmlnode.hpp"

#include <fstream>
#include <iostream>

XMLParser::XMLParser() : mpTree(NULL), mNodes(), mStates(), mFile(), mChar() { }

XMLTree* XMLParser::parse(const std::string& filename) {
	mpTree = new XMLTree();

	XMLState* begin = new XMLBegin();
	mStates.push(begin);

	handle_enter(begin);

	mFile.open(filename);

	if (!mFile.is_open()) {
		std::cout << "could not open the file " << filename << std::endl;
		std::exit(-1);
	}

	while ((mChar = mFile.get()) && !mStates.empty()) {
		StateCommand command = mStates.top()->process(*this);
		process_command(command);
	}

	mFile.close();

	if (!mNodes.empty()) {
		std::cout << "not all tags were closed!" << std::endl;
		std::exit(-1);
	}

	return mpTree;
}

void XMLParser::reset() {
	mpTree = NULL;
}

void XMLParser::handle_enter(XMLState* state) {
	StateCommand command = state->enter(*this);
	process_command(command);
}

void XMLParser::handle_exit(XMLState* state) {
	StateCommand command = state->exit(*this);
	process_command(command);
	delete state;
}

void XMLParser::process_command(const StateCommand &command) {
	StateAction action = command.first;
	XMLState* state = command.second;

	switch (action) {
	case StateAction::POP:
	{
		XMLState* top_state = mStates.top();
		mStates.pop();

		handle_exit(top_state);
		break;
	}
	case StateAction::PUSH:
		mStates.push(state);

		handle_enter(state);
		break;
	case StateAction::REPLACE:
	{
		XMLState* top_state = mStates.top();
		mStates.pop();

		handle_exit(top_state);

		mStates.push(state);

		handle_enter(state);
		break;
	}
	case StateAction::NIL:
		break;
	default:
		break;
	}
}

void XMLParser::add_node(XMLNode* node) {
	if (mNodes.empty()) {
		mpTree->mRoot = node;
	}

	else {
		mNodes.top()->add_child(node);
	}

	mNodes.push(node);
}