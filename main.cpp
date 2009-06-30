#include <stdio.h>  

extern int yyparse();

/*
void yyerror(const char *err_msg) 
{
	printf("ERR: %s",err_msg);
}
*/

int main(int argc,char **argv)
{

	yyparse();

	return 0;
}

