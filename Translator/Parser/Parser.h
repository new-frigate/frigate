#ifndef PARSER
#define PARSER

#include "Lexer.h"
#include "LexTag.h"

class Parser {

private:

	std::list<Tag *> * tags;
	std::vector<LexTag *> qu;

public:

	Parser();

	Parser(std::list<Tag *> * tags);

	void go();
};

#endif
