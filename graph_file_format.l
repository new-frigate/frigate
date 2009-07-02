%{
#include "graph_file_format.tab.hpp"
%}

CSYM [^\n]

%%
(#){CSYM}*(\n) {
			printf("Recognized text is: '%s'\n",yytext);			
			return COMMENT_STRING; 
		}
"<graph>"  { return GRAPH_BEGIN_TAG; }
"</graph>" { return GRAPH_END_TAG;  }
hello      { return HELLO;          }
. /* Any Symb */
%%

int yywrap(void){return 1;}

