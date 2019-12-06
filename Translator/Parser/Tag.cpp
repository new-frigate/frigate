#include "Tag.h"

Tag * GraphBeginTag::makeInst() {
	return new GraphBeginTag();
}

bool Tag::falarm(int cur, std::string * content)
{
	return false;
}

int Tag::doIterate(int cur, std::string * content) {
	return 0;
}

Tag * Tag::makeInst() {
	return new Tag();
}

Tag * GraphEndTag::makeInst() {
	return new GraphEndTag();
}

Tag * HeaderEndTag::makeInst() {
	return new HeaderEndTag();
}

Tag * HeaderBeginTag::makeInst()
{
	return new HeaderBeginTag;
}

Tag * RootBeginTag::makeInst()
{
	return new RootBeginTag;
}

Tag * RootEndTag::makeInst()
{
	return new RootEndTag;
}

Tag * TailBeginTag::makeInst()
{
	return new TailBeginTag;
}

Tag * TailEndTag::makeInst()
{
	return new TailEndTag;
}

Tag * VertexBeginTag::makeInst()
{
	return new VertexBeginTag;
}

Tag * VertexEndTag::makeInst()
{
	return new VertexEndTag;
}

Tag * SendBeginTag::makeInst()
{
	return new SendBeginTag;
}

Tag * SendEndTag::makeInst()
{
	return new SendEndTag;
}

Tag * RecvBeginTag::makeInst()
{
	return new RecvBeginTag;
}

Tag * RecvEndTag::makeInst()
{
	return new RecvEndTag;
}

Tag * FragmentBeginTag::makeInst()
{
	return new FragmentBeginTag;
}

Tag * FragmentEndTag::makeInst()
{
	return new FragmentEndTag;
}

Tag * InternalEdgeBeginTag::makeInst()
{
	return new InternalEdgeBeginTag;
}

Tag * InternalEdgeEndTag::makeInst()
{
	return new InternalEdgeEndTag;
}

Tag * ExternalEdgeBeginTag::makeInst()
{
	return new ExternalEdgeBeginTag;
}

Tag * ExternalEdgeEndTag::makeInst()
{
	return new ExternalEdgeEndTag;
}

Tag * ControlEdgeBeginTag::makeInst()
{
	return new ControlEdgeBeginTag;
}

Tag * ControlEdgeEndTag::makeInst()
{
	return new ControlEdgeEndTag;
}

Tag * EdgeTemplateBeginTag::makeInst()
{
	return new EdgeTemplateBeginTag;
}

Tag * EdgeTemplateEndTag::makeInst()
{
	return new EdgeTemplateEndTag;
}

Tag * VertexTemplateBeginTag::makeInst()
{
	return new VertexTemplateBeginTag;
}

Tag * VertexTemplateEndTag::makeInst()
{
	return new VertexTemplateEndTag;
}

Tag * CodeBeginTag::makeInst()
{
	return new CodeBeginTag;
}

Tag * CodeEndTag::makeInst()
{
	return new CodeEndTag;
}

Tag * ExchangeBeginTag::makeInst()
{
	return new ExchangeBeginTag;
}

Tag * ExchangeEndTag::makeInst()
{
	return new ExchangeEndTag;
}

Tag * SubgraphBeginTag::makeInst()
{
	return new SubgraphBeginTag;
}

Tag * SubgraphEndTag::makeInst()
{
	return new SubgraphEndTag;
}

Tag * VersionTag::makeInst()
{
	return new VersionTag;
}

Tag * IOVolumeTag::makeInst()
{
	return new IOVolumeTag;
}

Tag * CodeVolumeTag::makeInst()
{
	return new CodeVolumeTag;
}

Tag * MainSubraphTag::makeInst()
{
	return new MainSubraphTag;
}

Tag * HeaderTag::makeInst()
{
	return new HeaderTag;
}

Tag * RootTag::makeInst()
{
	return new RootTag;
}

Tag * TailTag::makeInst()
{
	return new TailTag;
}

Tag * NameTag::makeInst()
{
	return new NameTag;
}

Tag * TemplateTag::makeInst()
{
	return new TemplateTag;
}

Tag * ConditionTag::makeInst()
{
	return new ConditionTag;
}

Tag * FileTag::makeInst()
{
	return new FileTag;
}

Tag * SendTag::makeInst()
{
	return new SendTag;
}

Tag * RecvTag::makeInst()
{
	return new RecvTag;
}

Tag * VariableTag::makeInst()
{
	return new VariableTag;
}

Tag * TypeTag::makeInst()
{
	return new TypeTag;
}

Tag * LeftTag::makeInst()
{
	return new LeftTag;
}

Tag * RightTag::makeInst()
{
	return new RightTag;
}

Tag * CommentTag::makeInst()
{
	return new CommentTag;
}

int CommentTag::doIterate(int cur, std::string * content)
{
	this->value = "";
	int i;
	for (i = cur; i < content->size(); i++)
		if (content->at(i) == '\n')
			break;
		this->value += content->at(i);
	this->value += "\n";
	return i + 1;
}

Tag * PositiveFloatTag::makeInst()
{
	return new PositiveFloatTag;
}

int PositiveFloatTag::doIterate(int cur, std::string * content)
{
	bool notYetDot = true;
	std::string num = "";
	int i;
	for (i = cur; i < content->size() && (content->at(i) == '.' && notYetDot) || (content->at(i) >= '0' && content->at(i) <= '9'); i++) {
		if (content->at(i) == '.')
			notYetDot = false;
		num += content->at(i);
	}
	this->value = atof(num.c_str());
	return i;
}

Tag * StringTag::makeInst()
{
	return new StringTag;
}

int StringTag::doIterate(int cur, std::string * content)
{
	this->value = "";
	int i;
	for (i = cur + 1; i < content->size() && !(content->at(i) == '\"' && content->at(i - 1) != '\\'); i++)
		this->value += content->at(i);
	return i + 1;
}

bool StringTag::falarm(int cur, std::string * content)
{
	return !(content->at(cur) == '\"' && content->at(cur - 1) != '\\');
}

Tag * CodeClauseTag::makeInst()
{
	return new CodeClauseTag;
}

int CodeClauseTag::doIterate(int cur, std::string * content)
{
	this->value = "";
	int i;
	for (i = cur + 1; !(content->at(i) == '@' && content->at(i - 1) != '\\'); i++)
		this->value += content->at(i);
	return i + 1;
}

bool CodeClauseTag::falarm(int cur, std::string * content)
{
	return !(content->at(cur) == '@' && content->at(cur - 1) != '\\');
}

Tag * WhiteSpaceTag::makeInst()
{
	return new WhiteSpaceTag;
}

int WhiteSpaceTag::doIterate(int cur, std::string * content)
{
	int i;
	for (i = cur; i < content->size(); i++)
		if (content->at(i) != ' ' && content->at(i) != '\n' && content->at(i) != '\t' && content->at(i) != '\r')
			break;
	return i;
}

Tag * AssignTag::makeInst()
{
	return new AssignTag();
}

bool AssignTag::falarm(int cur, std::string * content)
{
	return content->at(cur - 1) == '=' || content->at(cur + 1) == '=';
}

Tag * OpenBracketTag::makeInst()
{
	return new OpenBracketTag();
}

Tag * CloseBracketTag::makeInst()
{
	return new CloseBracketTag();
}

Tag * CommaTag::makeInst()
{
	return new CommaTag();
}

Tag * ParameterTag::makeInst()
{
	return new ParameterTag();
}

Tag * ParametersBeginTag::makeInst()
{
	return new ParametersBeginTag();
}

Tag * ParametersEndTag::makeInst()
{
	return new ParametersEndTag();
}

Tag * ParameterNameTag::makeInst()
{
	return new ParameterNameTag();
}

bool ParameterNameTag::falarm(int cur, std::string* content) {
	if (cur + 1 < content->size() && cur - 3 >= 0) {
		if (std::isspace(content->at(cur + 1)) && std::isspace(content->at(cur - 3))) {
			return false;
		}
	}
	return true;
}

int ParameterNameTag::doIterate(int cur, std::string* content) {
	cur++;
	this->value = "";
	while (cur < content->size() && std::isspace(content->at(cur))) {
		cur++;
	}
	while (cur < content->size() && std::isalpha(content->at(cur))) {
		this->value += content->at(cur);
		cur++;
	}
	return cur;
}

Tag * UsingTag::makeInst() {
	return new UsingTag();
}

bool UsingTag::falarm(int cur, std::string* content) {
	if (cur + 1 < content->size()) {
		if(std::isspace(content->at(cur + 1))) {
			return false;
		}
	}
	return true;
}

int UsingTag::doIterate(int cur, std::string* content) {
	cur++;
	std::string word = "";
	while(cur + 1 < content->size()) {
		if (std::isalpha(content->at(cur))) {
			word += content->at(cur);
			cur++;
		}
		else {
			if (word.size() > 0) {
				this->value.push_back(word);
				word = "";
			}
			while (cur + 1 < content->size() && !std::isalpha(content->at(cur))) {

				if (content->at(cur) == ';') {
					return cur + 1;
				}
				cur++;
			}
		}
	}
	return cur;
}