all: parser

graph_file_format.tab.cpp: graph_file_format.ypp
	bison -d $^


lex.yy.c: graph_file_format.l
	flex $^


parser: graph_file_format.tab.cpp main.cpp lex.yy.c
	g++ -o $@ $^

clean:
	rm -rf graph_file_format.tab.cpp lex.yy.c graph_file_format.tab.hpp parser

