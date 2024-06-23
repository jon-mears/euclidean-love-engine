#ifndef XMLSTATE_HPP
#define XMLSTATE_HPP

class XMLParser;

#include <utility>

enum class StateAction {
	PUSH,
	POP,
	REPLACE,
	NIL
};

class XMLState;
typedef std::pair<StateAction, XMLState*> StateCommand;

class XMLState {
public:
	virtual ~XMLState();
	virtual StateCommand enter(XMLParser& parser);
	virtual StateCommand process(XMLParser& parser) = 0;
	virtual StateCommand exit(XMLParser& parser);
};

class XMLBegin : public XMLState {
public:
	virtual StateCommand enter(XMLParser& parser) override;
	virtual StateCommand process(XMLParser& parser) override;
	virtual StateCommand exit(XMLParser& parser) override;
};

class XMLTagname : public XMLState {
private:
	char mTagname[256];
	size_t mIndex;

public:
	virtual StateCommand enter(XMLParser& parser) override;
	virtual StateCommand process(XMLParser& parser) override;
	virtual StateCommand exit(XMLParser& parser) override;
};

class XMLTagCloser : public XMLState {
public:
	virtual StateCommand enter(XMLParser& parser) override;
	virtual StateCommand process(XMLParser& parser) override;
};

class XMLAttribName : public XMLState {
private:
	char mAttribName[256];
	size_t mIndex;
public:
	virtual StateCommand enter(XMLParser& parser) override;
	virtual StateCommand process(XMLParser& parser) override;
};

class XMLAttribNameCloser : public XMLState {
private:
	const std::string mAttribName;
public:
	XMLAttribNameCloser(char *attrib_name); 

	virtual StateCommand process(XMLParser& parser) override;
};

class XMLAttribValue : public XMLState {
private:
	const std::string mAttribName;
	char mAttribValue[256];
	size_t mIndex;
public:
	XMLAttribValue(char* attrib_name);
	XMLAttribValue(const std::string& attrib_name);

	virtual StateCommand enter(XMLParser& parser) override;
	virtual StateCommand process(XMLParser& parser) override;
	virtual StateCommand exit(XMLParser& parser) override;
};

class XMLContent : public XMLState {
private:
	char mContent[1024];
public:
	virtual StateCommand process(XMLParser& parser) override;
};

class XMLWhitespace : public XMLState {
public:
	virtual StateCommand process(XMLParser& parser) override;
};

#endif