#include "Lexer.h"

Lexer::Lexer(std::string * content) {
	text = content;
	tagMap.insert(std::pair<std::string, Tag *>(std::string("<graph>"), new GraphBeginTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("</graph>"), new GraphEndTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("<header>"), new HeaderBeginTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("</header>"), new HeaderEndTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("<root>"), new RootBeginTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("</root>"), new RootEndTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("<tail>"), new TailBeginTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("</tail>"), new TailEndTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("<vertex>"), new VertexBeginTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("</vertex>"), new VertexEndTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("<send>"), new SendBeginTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("</send>"), new SendEndTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("<recv>"), new RecvBeginTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("</recv>"), new RecvEndTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("<fragment>"), new FragmentBeginTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("</fragment>"), new FragmentEndTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("<internal_edge>"), new InternalEdgeBeginTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("</internal_edge>"), new InternalEdgeEndTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("<external_edge>"), new ExternalEdgeBeginTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("</external_edge>"), new ExternalEdgeEndTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("<control_edge>"), new ControlEdgeBeginTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("</control_edge>"), new ControlEdgeEndTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("<edge_template>"), new EdgeTemplateBeginTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("</edge_template>"), new EdgeTemplateEndTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("<vertex_template>"), new VertexTemplateBeginTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("</vertex_template>"), new VertexTemplateEndTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("<code>"), new CodeBeginTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("</code>"), new CodeEndTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("<exchange>"), new ExchangeBeginTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("</exchange>"), new ExchangeEndTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("<subgraph>"), new SubgraphBeginTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("</subgraph>"), new SubgraphEndTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("version"), new VersionTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("io_volume"), new IOVolumeTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("code_volume"), new CodeVolumeTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("main_subgraph"), new MainSubraphTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("header"), new HeaderTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("root"), new RootTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("tail"), new TailTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("name"), new NameTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("template"), new TemplateTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("condition"), new ConditionTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("file"), new FileTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("send"), new SendTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("recv"), new RecvTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("variable"), new VariableTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("type"), new TypeTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("left"), new LeftTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("right"), new RightTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("#"), new CommentTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("\""), new StringTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("@"), new CodeClauseTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string(" "), new WhiteSpaceTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("\n"), new WhiteSpaceTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("\r"), new WhiteSpaceTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("\t"), new WhiteSpaceTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("="), new AssignTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("("), new OpenBracketTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string(")"), new CloseBracketTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string(","), new CommaTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("parameter"), new ParameterTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("<parameters>"), new ParametersBeginTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("</parameters>"), new ParametersEndTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("var"), new ParameterNameTag()));
	tagMap.insert(std::pair<std::string, Tag *>(std::string("using"), new UsingTag()));
}

std::list<Tag*>* Lexer::go() {
	std::list<Tag *> * vector = new std::list<Tag *>();
	int iterator = 1;
	std::string word = "";
	for (iterator = 1; iterator < this->text->size(); iterator++) {
		
		word += this->text->at(iterator);

		if (this->tagMap.find(word) != this->tagMap.end()) {
                    Tag * tt = this->tagMap.at(word);
                    if (!tt->falarm(iterator, this->text)) {
                            //std::cout << vector->size() << std::endl;
                            word = "";
                            Tag * tag = tt->makeInst();
                            if (tag->letIterate) {
                                    iterator = tag->doIterate(iterator, this->text) - 1;
                            }
                            vector->push_back(tag);
                    }
		}
		else {
			if (word.size() == 1 && word.c_str()[0] >= '0' && word.c_str()[0] <= '9') {
				Tag * tag = new PositiveFloatTag();
				iterator = tag->doIterate(iterator, this->text) - 1;
				vector->push_back(tag);
				word = "";
			}
		}
	}
	return vector;
}
