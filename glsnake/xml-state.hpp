#ifndef XML_STATE_HPP
#define XML_STATE_HPP

class XMLParser;

#include <utility>
#include <string>

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
	virtual StateCommand Enter(XMLParser& rParser);
	virtual StateCommand Process(XMLParser& rParser) = 0;
	virtual StateCommand Exit(XMLParser& rParser);
};

class XMLBegin : public XMLState {
public:
	virtual StateCommand Enter(XMLParser& rParser) override;
	virtual StateCommand Process(XMLParser& rParser) override;
	virtual StateCommand Exit(XMLParser& rParser) override;
};

class XMLTag : public XMLState {
public:
	virtual StateCommand Enter(XMLParser& rParser) override;
	virtual StateCommand Process(XMLParser& rParser) override;
};

class XMLBeginTagname : public XMLState {
private:
	char mTagname[256];
	size_t mIndex;

public:
	virtual StateCommand Process(XMLParser& rParser) override;
	virtual StateCommand Exit(XMLParser& rParser) override;
};

class XMLTagCloser : public XMLState {
public:
	virtual StateCommand Enter(XMLParser& rParser) override;
	virtual StateCommand Process(XMLParser& rParser) override;
};

class XMLAttribName : public XMLState {
private:
	char mAttribName[256];
	size_t mIndex;
public:
	virtual StateCommand Enter(XMLParser& rParser) override;
	virtual StateCommand Process(XMLParser& rParser) override;
};

class XMLAttribNameCloser : public XMLState {
private:
	const std::string mAttribName;
public:
	XMLAttribNameCloser(char *pAttribName); 

	virtual StateCommand Process(XMLParser& rParser) override;
};

class XMLAttribValue : public XMLState {
private:
	const std::string mAttribName;
	char mAttribValue[256];
	size_t mIndex;
public:
	XMLAttribValue(char* pAttribName);
	XMLAttribValue(const std::string& rcAttribName);

	virtual StateCommand Enter(XMLParser& rParser) override;
	virtual StateCommand Process(XMLParser& rParser) override;
	virtual StateCommand Exit(XMLParser& rParser) override;
};

class XMLContent : public XMLState {
private:
	char mContent[1024];
	size_t mIndex;
public:
	virtual StateCommand Process(XMLParser& rParser) override;
	virtual StateCommand Exit(XMLParser& rParser) override;
};

class XMLEndTagname : public XMLState {
private:
	char mTagname[512];
	size_t mIndex;
public:
	virtual StateCommand Enter(XMLParser& rParser) override;
	virtual StateCommand Process(XMLParser& rParser) override;
	virtual StateCommand Exit(XMLParser& rParser) override;
};

class XMLWhitespace : public XMLState {
public:
	virtual StateCommand Process(XMLParser& rParser) override;
};

#endif