#ifndef LEXER
#define LEXER

#include <string>
#include <map>
#include "Tag.h"
#include <list>

#include <iostream>

class Lexer {

private:
	std::string * text;
	std::map<std::string, Tag *> tagMap;
public:

	Lexer(std::string * content);

	std::list<Tag *> * go();
};

#endif
