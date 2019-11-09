#ifndef HEXPARSER
#define HEXPARSER

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include "Lexer.h"
#include "Parser.h"
#include "../Exceptions/Excepion.h"

void vect_print(std::list<Tag *> *vector);

graph *parse(std::string name_of_file);

#endif
