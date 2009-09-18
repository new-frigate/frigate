%{
#define YYSTYPE char*
#include "graph_file_format.tab.hpp"
#include <stdlib.h>
%}

CSYM [^\n]
NUMBER [0-9]+

%%
"<graph>"                      { return GRAPH_BEGIN_TAG;            }
"</graph>"                     { return GRAPH_END_TAG;              }
"<header>"                     { return HEADER_BEGIN_TAG;           }
"</header>"                    { return HEADER_END_TAG;             }
"<root>"                       { return ROOT_BEGIN_TAG;             }
"</root>"                      { return ROOT_END_TAG;               }
"<tail>"                       { return TAIL_BEGIN_TAG;             }
"</tail>"                      { return TAIL_END_TAG;               }
"<vertex>"                     { return VERTEX_BEGIN_TAG;           }
"</vertex>"                    { return VERTEX_END_TAG;             }
"<code>"                       { return CODE_BEGIN_TAG;             }
"</code>"                      { return CODE_END_TAG;               }
"<exchange>"                   { return EXCHANGE_BEGIN_TAG;         }
"</exchange>"                  { return EXCHANGE_END_TAG;           }
"<subgraph>"                   { return SUBGRAPH_BEGIN_TAG;         }
"</subgraph>"                  { return SUBGRAPH_END_TAG;           }
"version"                      { return VERSION_KEY_WORD;           }
"main_subgraph"                { return MAIN_SUBGRAPH_KEY_WORD;     }
"header"                       { return HEADER_KEY_WORD;            }
"root"                         { return ROOT_KEY_WORD;              }
"tail"                         { return TAIL_KEY_WORD;              }
"name"                         { return NAME_KEY_WORD;              }
"template"                     { return TEMPLATE_NAME_KEY_WORD;     }
"condition"                    { return CONDITION_KEY_WORD;         }
(#){CSYM}*(\n)                 {  /* printf("Recognized text is: '%s'\n",yytext);	*/		
			                      return COMMENT_STRING; 
                               }
{NUMBER}\.{NUMBER}             { 
                                    printf("value: '%s'\n",yytext);
                                    *yylval=yytext;
                                    return POSITIVE_FLOAT_POINT_VALUE; 
                               }
\"([^"\\]|\\.)*(\")            {  /* This rule parsing some like:
                                          "asdasds \"aaa\" bbvnb"
                                   */ 
                                    *yylval=&(yytext[1]);
                                    yytext[yyleng-1]='\0';
                                    return STRING_VALUE;  
                               }
(@)([^@\\]|\\.)*(@)            {  /* This rule parse code for graph */
                                  *yylval=&(yytext[1]);
                                  yytext[yyleng-1]='\0';
                                  return CODE_CLAUSE;
                               }
[ \t\n\r]+                     { return WHITE_SPACE;                }
.                              { return yytext[0]; /* Any Symb */   }
%%

int yywrap(void){return 1;}

