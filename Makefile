# Commented, because to much noise in stderr
# FLEX_DEBUG_FLAG=-d
# BISON_DEBUG_FLAG="-DYYDEBUG=1"


#BISON=/opt/bison-3.0.2/bin/bison
BISON=bison

all: parser

graph_file_format.tab.cpp: graph_file_format.ypp
	$(BISON) -d $^


lex.yy.c: graph_file_format.l
	flex  --bison-bridge --bison-locations $(FLEX_DEBUG_FLAG) $^


parser:		core/char_names.cpp \
		core/graph/code_block.cpp \
		core/graph/vertex.cpp \
		core/graph/edge.cpp \
		core/graph/subgraph.cpp \
		core/graph/graph.cpp \
		core/graph_touch.cpp \
		core/line_dynamic_array_int.cpp \
		graph_file_format.tab.cpp \
		main.cpp \
		lex.yy.c
	g++ -g $(BISON_DEBUG_FLAG) -o $@ $^
	
clean:
	rm -rf graph_file_format.tab.cpp lex.yy.c graph_file_format.tab.hpp parser

