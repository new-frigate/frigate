#include <stdio.h>  

extern int yyparse();
extern int yydebug;

/*
void yyerror(const char *err_msg) 
{
	printf("ERR: %s",err_msg);
}
*/

int main(int argc,char **argv)
{

	yydebug=1;
	yyparse();

	return 0;
}

