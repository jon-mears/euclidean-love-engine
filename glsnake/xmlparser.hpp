#ifndef XMLPARSER_HPP
#define XMLPARSER_HPP

#include <string>
#include <stack>
#include <fstream>

class XMLTree;
class XMLState;

// this can be easily generalized to an abstract pushdown automaton
// text parser
class XMLParser {
private:
	XMLTree* mpTree;
	std::stack<XMLNode*> mNodes;
	std::stack<XMLState*> mStates;
	std::ifstream mFile;
	char mChar;

	void handle_enter(XMLState* state);
	void handle_exit(XMLState* state);
	void process_command(const StateCommand& command);
public:
	XMLParser();
	XMLTree *parse(const std::string &filename);
	void reset();

	friend class XMLBegin;
	friend class XMLTagname;
	friend class XMLAttribName;
	friend class XMLAttribValue;
	friend class XMLContent;
	friend class XMLWhitespace;
	friend class XMLTagCloser;
	friend class XMLAttribNameCloser;
};
#endif