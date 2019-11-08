#ifndef TAG
#define TAG

#include <string>

class Tag {

public:
	std::string nameOfClass;
	Tag() {
		this->nameOfClass = "Tag";
	}
	bool letIterate = false;
	virtual bool falarm(int cur, std::string * content);
	virtual int doIterate(int cur, std::string * content);
	virtual Tag *makeInst();
};

class GraphBeginTag: public Tag {
public:
	GraphBeginTag() {
		this->nameOfClass = "GraphBeginTag";
	}
	Tag *makeInst();
};

class GraphEndTag: public Tag {
public:
	GraphEndTag() {
		this->nameOfClass = "GraphEndTag";
	}
	Tag *makeInst();
};

class HeaderBeginTag : public Tag {
public:
	HeaderBeginTag() {
		this->nameOfClass = "HeaderBeginTag";
	}
	Tag *makeInst();
};

class HeaderEndTag : public Tag {
public:
	HeaderEndTag() {
		this->nameOfClass = "HeaderEndTag";
	}
	Tag *makeInst();
};

class RootBeginTag : public Tag {
public:
	RootBeginTag() {
		this->nameOfClass = "RootBeginTag";
	}
	Tag *makeInst();
};

class RootEndTag : public Tag {
public:
	RootEndTag() {
		this->nameOfClass = "RootEndTag";
	}
	Tag *makeInst();
};

class TailBeginTag : public Tag {
public:
	TailBeginTag() {
		this->nameOfClass = "TailBeginTag";
	}
	Tag *makeInst();
};

class TailEndTag : public Tag {
public:
	TailEndTag() {
		this->nameOfClass = "TailEndTag";
	}
	Tag *makeInst();
};

class VertexBeginTag : public Tag {
public:
	VertexBeginTag() {
		this->nameOfClass = "VertexBeginTag";
	}
	Tag *makeInst();
};

class VertexEndTag : public Tag {
public:
	VertexEndTag() {
		this->nameOfClass = "VertexEndTag";
	}
	Tag *makeInst();
};

class SendBeginTag : public Tag {
public:
	SendBeginTag() {
		this->nameOfClass = "SendBeginTag";
	}
	Tag *makeInst();
};

class SendEndTag : public Tag {
public:
	SendEndTag() {
		this->nameOfClass = "SendEndTag";
	}
	Tag *makeInst();
};

class RecvBeginTag : public Tag {
public:
	RecvBeginTag() {
		this->nameOfClass = "RecvBeginTag";
	}
	Tag *makeInst();
};

class RecvEndTag : public Tag {
public:
	RecvEndTag() {
		this->nameOfClass = "RecvEndTag";
	}
	Tag *makeInst();
};

class FragmentBeginTag : public Tag {
public:
	FragmentBeginTag() {
		this->nameOfClass = "FragmentBeginTag";
	}
	Tag *makeInst();
};

class FragmentEndTag : public Tag {
public:
	FragmentEndTag() {
		this->nameOfClass = "FragmentEndTag";
	}
	Tag *makeInst();
};

class InternalEdgeBeginTag : public Tag {
public:
	InternalEdgeBeginTag() {
		this->nameOfClass = "InternalEdgeBeginTag";
	}
	Tag *makeInst();
};

class InternalEdgeEndTag : public Tag {
public:
	InternalEdgeEndTag() {
		this->nameOfClass = "InternalEdgeEndTag";
	}
	Tag *makeInst();
};

class ExternalEdgeBeginTag : public Tag {
public:
	ExternalEdgeBeginTag() {
		this->nameOfClass = "ExternalEdgeBeginTag";
	}
	Tag *makeInst();
};

class ExternalEdgeEndTag : public Tag {
public:
	ExternalEdgeEndTag() {
		this->nameOfClass = "ExternalEdgeEndTag";
	}
	Tag *makeInst();
};

class ControlEdgeBeginTag : public Tag {
public:
	ControlEdgeBeginTag() {
		this->nameOfClass = "ControlEdgeBeginTag";
	}
	Tag *makeInst();
};

class ControlEdgeEndTag : public Tag {
public:
	ControlEdgeEndTag() {
		this->nameOfClass = "ControlEdgeEndTag";
	}
	Tag *makeInst();
};

class EdgeTemplateBeginTag : public Tag {
public:
	EdgeTemplateBeginTag() {
		this->nameOfClass = "EdgeTemplateBeginTag";
	}
	Tag *makeInst();
};

class EdgeTemplateEndTag : public Tag {
public:
	EdgeTemplateEndTag() {
		this->nameOfClass = "EdgeTemplateEndTag";
	}
	Tag *makeInst();
};

class VertexTemplateBeginTag : public Tag {
public:
	VertexTemplateBeginTag() {
		this->nameOfClass = "VertexTemplateBeginTag";
	}
	Tag *makeInst();
};

class VertexTemplateEndTag : public Tag {
public:
	VertexTemplateEndTag() {
		this->nameOfClass = "VertexTemplateEndTag";
	}
	Tag *makeInst();
};

class CodeBeginTag : public Tag {
public:
	CodeBeginTag() {
		this->nameOfClass = "CodeBeginTag";
	}
	Tag *makeInst();
};

class CodeEndTag : public Tag {
public:
	CodeEndTag() {
		this->nameOfClass = "CodeEndTag";
	}
	Tag *makeInst();
};

class ExchangeBeginTag : public Tag {
public:
	ExchangeBeginTag() {
		this->nameOfClass = "ExchangeBeginTag";
	}
	Tag *makeInst();
};

class ExchangeEndTag : public Tag {
public:
	ExchangeEndTag() {
		this->nameOfClass = "ExchangeEndTag";
	}
	Tag *makeInst();
};

class SubgraphBeginTag : public Tag {
public:
	SubgraphBeginTag() {
		this->nameOfClass = "SubgraphBeginTag";
	}
	Tag *makeInst();
};

class SubgraphEndTag : public Tag {
public:
	SubgraphEndTag() {
		this->nameOfClass = "SubgraphEndTag";
	}
	Tag *makeInst();
};

class VersionTag : public Tag {
public:
	VersionTag() {
		this->nameOfClass = "VersionTag";
	}
	Tag *makeInst();
};

class IOVolumeTag : public Tag {
public:
	IOVolumeTag() {
		this->nameOfClass = "IOVolumeTag";
	}
	Tag *makeInst();
};

class CodeVolumeTag : public Tag {
public:
	CodeVolumeTag() {
		this->nameOfClass = "CodeVolumeTag";
	}
	Tag *makeInst();
};

class MainSubraphTag : public Tag {
public:
	MainSubraphTag() {
		this->nameOfClass = "MainSubraphTag";
	}
	Tag *makeInst();
};

class HeaderTag : public Tag {
public:
	HeaderTag() {
		this->nameOfClass = "HeaderTag";
	}
	Tag *makeInst();
};

class RootTag : public Tag {
public:
	RootTag() {
		this->nameOfClass = "RootTag";
	}
	Tag *makeInst();
};

class TailTag : public Tag {
public:
	TailTag() {
		this->nameOfClass = "TailTag";
	}
	Tag *makeInst();
};

class NameTag : public Tag {
public:
	NameTag() {
		this->nameOfClass = "NameTag";
	}
	Tag *makeInst();
};

class TemplateTag : public Tag {
public:
	TemplateTag() {
		this->nameOfClass = "TemplateTag";
	}
	Tag *makeInst();
};

class ConditionTag : public Tag {
public:
	ConditionTag() {
		this->nameOfClass = "ConditionTag";
	}
	Tag *makeInst();
};

class FileTag : public Tag {
public:
	FileTag() {
		this->nameOfClass = "FileTag";
	}
	Tag *makeInst();
};

class SendTag : public Tag {
public:
	SendTag() {
		this->nameOfClass = "SendTag";
	}
	Tag *makeInst();
};

class RecvTag : public Tag {
public:
	RecvTag() {
		this->nameOfClass = "RecvTag";
	}
	Tag *makeInst();
};

class VariableTag : public Tag {
public:
	VariableTag() {
		this->nameOfClass = "VariableTag";
	}
	Tag *makeInst();
};

class TypeTag : public Tag {
public:
	TypeTag() {
		this->nameOfClass = "TypeTag";
	}
	Tag *makeInst();
};

class LeftTag : public Tag {
public:
	LeftTag() {
		this->nameOfClass = "LeftTag";
	}
	Tag *makeInst();
};

class RightTag : public Tag {
public:
	RightTag() {
		this->nameOfClass = "RightTag";
	}
	Tag *makeInst();
};

class CommentTag : public Tag {
public:
	CommentTag() {
		this->nameOfClass = "CommentTag";
		this->letIterate = true;
	}
	std::string value;
	Tag *makeInst();
	int doIterate(int cur, std::string * content);
};

class PositiveFloatTag : public Tag {
public:
	PositiveFloatTag() {
		nameOfClass = "PositiveFloatTag";
		letIterate = true;
	}
	
	float value;
	Tag *makeInst();
	int doIterate(int cur, std::string * content);
};

class StringTag : public Tag {
public:
	StringTag() {
		nameOfClass = "StringTag";
		letIterate = true;
	}
	std::string value;
	Tag *makeInst();
	int doIterate(int cur, std::string * content);
	bool falarm(int cur, std::string * content);
};

class CodeClauseTag : public Tag {
public:
	CodeClauseTag() {
		nameOfClass = "CodeClauseTag";
		letIterate = true;
	}
	std::string value;
	Tag *makeInst();
	int doIterate(int cur, std::string * content);
	bool falarm(int cur, std::string * content);
};

class WhiteSpaceTag : public Tag {
public:

	WhiteSpaceTag() {
		this->nameOfClass = "WhiteSpaceTag";
		this->letIterate = true;
	}
	Tag *makeInst();
	int doIterate(int cur, std::string * content);
};

class AssignTag : public Tag {
public:
	AssignTag() {
		this->nameOfClass = "AssignTag";
	}
	Tag *makeInst();
	bool falarm(int cur, std::string * content);
};

class OpenBracketTag : public Tag {
public:
	OpenBracketTag() {
		this->nameOfClass = "OpenBracketTag";
	}
	Tag *makeInst();
};

class CloseBracketTag : public Tag {
public:
	CloseBracketTag() {
		this->nameOfClass = "CloseBracketTag";
	}
	Tag *makeInst();
};

class CommaTag : public Tag {
public:
	CommaTag() {
		this->nameOfClass = "CommaTag";
	}
	Tag *makeInst();
};

#endif
