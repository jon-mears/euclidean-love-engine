#ifndef XML_PARSER_HPP
#define XML_PARSER_HPP

#include <string>
#include <stack>
#include <fstream>
#include <utility>

enum class StateAction;

class XMLTree;
class XMLState;
class XMLNode;

typedef std::pair<StateAction, XMLState*> StateCommand;

// this can be easily generalized to an abstract pushdown automaton
// text parser
class XMLParser {
private:
	XMLTree* mpTree;
	std::stack<XMLNode*> mNodes;
	std::stack<XMLState*> mStates;
	std::ifstream mFile;
	char mChar;

	void HandleEnter(XMLState* pState);
	void HandleExit(XMLState* pState);
	void ProcessCommand(const StateCommand &rcCommand);
	void AddNode(XMLNode* pNode);
public:
	XMLParser();
	XMLTree *Parse(const std::string &rcFilename);
	void Reset();

	friend class XMLBegin;
	friend class XMLTag;
	friend class XMLBeginTagname;
	friend class XMLAttribName;
	friend class XMLAttribValue;
	friend class XMLContent;
	friend class XMLWhitespace;
	friend class XMLTagCloser;
	friend class XMLAttribNameCloser;
	friend class XMLEndTagname;
};
#endif