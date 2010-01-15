# Commented, because to much noise in stderr
# FLEX_DEBUG_FLAG=-d
# BISON_DEBUG_FLAG="-DYYDEBUG=1"

all: parser

graph_file_format.tab.cpp: graph_file_format.ypp
	bison -d $^


lex.yy.c: graph_file_format.l
	flex  --bison-bridge --bison-locations $(FLEX_DEBUG_FLAG) $^


parser: graph_file_format.tab.cpp main.cpp lex.yy.c
	g++ -g $(BISON_DEBUG_FLAG) -o $@ $^

clean:
	rm -rf graph_file_format.tab.cpp lex.yy.c graph_file_format.tab.hpp parser

