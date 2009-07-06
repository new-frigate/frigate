%{
#define YYSTYPE char*
#include "graph_file_format.tab.hpp"
#include <stdlib.h>
%}

CSYM [^\n]
NUMBER [0-9]+

%%
(#){CSYM}*(\n) {
			/* printf("Recognized text is: '%s'\n",yytext);	*/		
			return COMMENT_STRING; 
		}
"<graph>"                      { return GRAPH_BEGIN_TAG;            }
"</graph>"                     { return GRAPH_END_TAG;              }
"hello"                        { return HELLO;                      }
"version"                      { return VERSION_KEY_WORD;           }
{NUMBER}\.{NUMBER}             { 
                                    printf("value: '%s'\n",yytext);
                                    *yylval=yytext;
                                    return POSITIVE_FLOAT_POINT_VALUE; 
                               }
[ \t\n\r]+                     { return WHITE_SPACE;                }
.                              { return yytext[0]; /* Any Symb */   }
%%

int yywrap(void){return 1;}

