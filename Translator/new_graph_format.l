"<graph>"		GRAPH_BEGIN_TAG;
                                             
"</graph>"		GRAPH_END_TAG;

"<header>"		HEADER_BEGIN_TAG;

"</header>"		HEADER_END_TAG;

"<root>"      	 	ROOT_BEGIN_TAG;

"</root>"   	   	ROOT_END_TAG;

"<tail>"   	    	TAIL_BEGIN_TAG;

"</tail>"    	  	TAIL_END_TAG;

"<vertex>"     		VERTEX_BEGIN_TAG;

"</vertex>" 	   	VERTEX_END_TAG;

"<send>"      		SEND_BEGIN_TAG;
                                              
"</send>"   	 	SEND_END_TAG;
                                              
"<recv>"      	 	RECV_BEGIN_TAG;
                                              
"</recv>"  	    	RECV_END_TAG;
                                              
"<fragment>"  		FRAGMENT_BEGIN_TAG;
                                              
"</fragment>"	 	FRAGMENT_END_TAG;
                                              
"<internal_edge>"	INTERNAL_EDGE_BEGIN_TAG;
                                     
"</internal_edge>"     	INTERNAL_EDGE_END_TAG;
                                       
"<external_edge>"      	EXTERNAL_EDGE_BEGIN_TAG;
                                     
"</external_edge>"      EXTERNAL_EDGE_END_TAG;
                                       
"<control_edge>"        CONTROL_EDGE_BEGIN_TAG;
                                     
"</control_edge>"       CONTROL_EDGE_END_TAG;
                                       
"<edge_template>"       EDGE_TEMPLATE_BEGIN_TAG;
                                     
"</edge_template>"      EDGE_TEMPLATE_END_TAG;
                                       
"<vertex_template>"     VERTEX_TEMPLATE_BEGIN_TAG;
                                     
"</vertex_template>"    VERTEX_TEMPLATE_END_TAG;
                                       
"<code>"                CODE_BEGIN_TAG;
                                              
"</code>"               CODE_END_TAG;
                                                
"<exchange>"            EXCHANGE_BEGIN_TAG;
                                          
"</exchange>"           EXCHANGE_END_TAG;
                                            
"<subgraph>"            SUBGRAPH_BEGIN_TAG;
                                          
"</subgraph>"           SUBGRAPH_END_TAG;
                                            
"version"               VERSION_KEY_WORD;
                                            
"io_volume"             IO_VOLUME_KEY_WORD;
                                            
"code_volume"           CODE_VOLUME_KEY_WORD;
                                            
"main_subgraph"         MAIN_SUBGRAPH_KEY_WORD;
                                      
"header"                HEADER_KEY_WORD;
                                             
"root"                  ROOT_KEY_WORD;
                                               
"tail"                  TAIL_KEY_WORD;
                                               
"name"                  NAME_KEY_WORD;
                                               
"template"              TEMPLATE_NAME_KEY_WORD;
                                      
"condition"             CONDITION_KEY_WORD;
                                          
"file"                  FILE_KEY_WORD;
                                               
"send"                 	SEND_KEY_WORD;
                                               
"recv"                 	RECV_KEY_WORD;
                                               
"variable"             	VARIABLE_KEY_WORD;
                               
"type"                 	TYPE_KEY_WORD;

"left"                  LEFT_KEY_WORD;

"right"                 RIGHT_KEY_WORD;

(#){CSYM}*(\n)       	COMMENT_STRING; 

{NUMBER}\.{NUMBER}     	POSITIVE_FLOAT_POINT_VALUE; 

\"([^"\\]|\\.)*(\")   	STRING_VALUE;  

(@)([^@\\]|\\.)*(@)    	CODE_CLAUSE;

[ \t\n\r]+            	WHITE_SPACE;

