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

	FILE *f=NULL;
	FILE *buf;
	int flag;
	if(argc<2)
	{
		printf("Incorrect arguments\n");
		return -1; 
	}

	f=fopen(argv[1],"r");
	if(f==NULL)
	{
		printf("Can't open file with name '%s'\n",argv[1]);
		return 1;
	}

	yydebug=1;

	buf=stdin;
	stdin=f;
	flag=yyparse();
	fclose(f);
	stdin=buf;

	printf("Parsing finished with value %d\n",flag);

	return 0;
}

