%{
#include "graph_file_format.tab.hpp"
%}

CSYM [^\n]

%%
{CSYM}* { return COMMENT_STRING; }

%%

int yywrap(void){return 1;}

