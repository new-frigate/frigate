%{
#define YYSTYPE char*
#include "graph_file_format.tab.hpp"
#include <stdlib.h>
/*
#define YY_INPUT(buf,result,max_size) my_input((buf),(result),(max_size),yylloc)



void my_input(char *buf,size_t read_bytes,size_t max_size,YYLTYPE *yylloc);
*/
%}

CSYM [^\n]
NUMBER [0-9]+

%%
"<graph>"                      { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return GRAPH_BEGIN_TAG;            }
"</graph>"                     { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return GRAPH_END_TAG;              }
"<header>"                     { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return HEADER_BEGIN_TAG;           }
"</header>"                    { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return HEADER_END_TAG;             }
"<root>"                       { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return ROOT_BEGIN_TAG;             }
"</root>"                      { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return ROOT_END_TAG;               }
"<tail>"                       { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return TAIL_BEGIN_TAG;             }
"</tail>"                      { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return TAIL_END_TAG;               }
"<vertex>"                     { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return VERTEX_BEGIN_TAG;           }
"</vertex>"                    { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return VERTEX_END_TAG;             }
"<internal_edge>"              { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return INTERNAL_EDGE_BEGIN_TAG;    }
"</internal_edge>"             { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return INTERNAL_EDGE_END_TAG;      }
"<external_edge>"              { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return EXTERNAL_EDGE_BEGIN_TAG;    }
"</external_edge>"             { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return EXTERNAL_EDGE_END_TAG;      }
"<code>"                       { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return CODE_BEGIN_TAG;             }
"</code>"                      { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return CODE_END_TAG;               }
"<block>"                      { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return BLOCK_BEGIN_TAG;            }
"</block>"                     { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return BLOCK_END_TAG;              }
"<exchange>"                   { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return EXCHANGE_BEGIN_TAG;         }
"</exchange>"                  { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return EXCHANGE_END_TAG;           }
"<subgraph>"                   { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return SUBGRAPH_BEGIN_TAG;         }
"</subgraph>"                  { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return SUBGRAPH_END_TAG;           }
"version"                      { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return VERSION_KEY_WORD;           }
"main_subgraph"                { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return MAIN_SUBGRAPH_KEY_WORD;     }
"header"                       { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return HEADER_KEY_WORD;            }
"root"                         { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return ROOT_KEY_WORD;              }
"tail"                         { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return TAIL_KEY_WORD;              }
"name"                         { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return NAME_KEY_WORD;              }
"template"                     { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return TEMPLATE_NAME_KEY_WORD;     }
"condition"                    { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return CONDITION_KEY_WORD;         }
"file"                         { yylloc->first_line=yylloc->last_line; yylloc->first_column=yylloc->last_column; yylloc->last_column+=strlen(yytext);  return FILE_KEY_WORD;              }
(#){CSYM}*(\n)                 {  /* printf("Recognized text is: '%s'\n",yytext);	*/
                                  yylloc->first_column=yylloc->last_column;
                                  yylloc->last_column=1;
                                  yylloc->first_line=yylloc->last_line;
                                  yylloc->last_line++;	
                                  return COMMENT_STRING; 
                               }
{NUMBER}\.{NUMBER}             { 
                                    printf("value: '%s'\n",yytext);
                                    *yylval=yytext;
                                    yylloc->first_column=yylloc->last_column;
                                    yylloc->last_column+=strlen(yytext);
                                    return POSITIVE_FLOAT_POINT_VALUE; 
                               }
\"([^"\\]|\\.)*(\")            {  /* This rule parsing some like:
                                          "asdasds \"aaa\" bbvnb"
                                   */
                                    {
                                      register int i;
                                      register int columns=0;
                                      int strings=0;
                                      register int length;
                                      length=strlen(yytext);
                                      for(i=0;i<length;i++)
                                      {
                                        if(yytext[i]=='\n')
                                        {
                                          strings++;
                                          columns=0;
                                        }
                                        columns++;
                                      }
                                      yylloc->first_line=yylloc->last_line;
                                      yylloc->last_line+=strings;
                                      yylloc->first_column=yylloc->last_column;
                                      yylloc->last_column=columns;
                                    }
                                    *yylval=&(yytext[1]);
                                    yytext[yyleng-1]='\0';
                                    return STRING_VALUE;  
                               }
(@)([^@\\]|\\.)*(@)            {  /* This rule parse code for graph */
                                    {
                                      register int i;
                                      register int columns=0;
                                      int strings=0;
                                      register int length;
                                      length=strlen(yytext);
                                      for(i=0;i<length;i++)
                                      {
                                        if(yytext[i]=='\n')
                                        {
                                          strings++;
                                          columns=0;
                                        }
                                        columns++;
                                      }
                                      yylloc->first_line=yylloc->last_line;
                                      yylloc->last_line+=strings;
                                      yylloc->first_column=yylloc->last_column;
                                      yylloc->last_column=columns;
                                    }

                                  *yylval=&(yytext[1]);
                                  yytext[yyleng-1]='\0';
                                  return CODE_CLAUSE;
                               }
[ \t\n\r]+                     {
                                    {
                                      register int i;
                                      register int columns=0;
                                      int strings=0;
                                      register int length;
                                      length=strlen(yytext);
                                      for(i=0;i<length;i++)
                                      {
                                        if(yytext[i]=='\n')
                                        {
                                          strings++;
                                          columns=0;
                                        }
                                        columns++;
                                      }
                                      yylloc->first_line=yylloc->last_line;
                                      yylloc->last_line+=strings;
                                      yylloc->first_column=yylloc->last_column;
                                      yylloc->last_column=columns;
                                    }
                                    return WHITE_SPACE;
                               }
.                              {  /* Any Symb */
                                    
                                    yylloc->first_column=yylloc->last_column;
                                    if(yytext[0]=='\n')
                                    {
                                       yylloc->last_line++;
                                       yylloc->last_column=0;
                                    }                                  
                                    yylloc->last_column++;                                    
                                    return yytext[0]; 
                               }
%%

int yywrap(void){return 1;}

/*
void my_input(char *buf,size_t read_bytes,size_t max_size,YYLTYPE *location)
{
	read_bytes=fread(buf,sizeof(char),max_size,yyin);
		
	return;
}
*/

