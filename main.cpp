#include <stdio.h>
#include "core/graph.h"

extern int yyparse(frigate::Graph *graph);
extern int yydebug;

/*
 void yyerror(const char *err_msg)
 {
 printf("ERR: %s",err_msg);
 }

 */

using namespace frigate;

int main(int argc, char **argv) {
	FILE *f = NULL;
	FILE *buf;
	int flag;
	if (argc < 2) {
		printf("Incorrect arguments\n");
		return -1;
	}

	f = fopen(argv[1], "r");
	if (f == NULL) {
		printf("Can't open file with name '%s'\n", argv[1]);
		return 1;
	}

	/* yydebug=1; */

	buf = stdin;
	stdin = f;

	Graph graph;
	flag = yyparse(&graph);

	stdin = buf;
	printf("Parsing finished with value %d\n", flag);

	if (!flag) {
		graph.toFile("test.txt");
	}

	fclose(f);

	return 0;
}

