#ifndef __FRIGATE_GHAPH_H__
#define __FRIGATE_GHAPH_H__

#include "frigate_types.h"
#include "char_names.h"

#include "line_dynamic_array.h"


namespace frigate
{

    class Graph
    {
	protected:
		float version;
		
		Code_block header;
		Code_block root;
		Code_block tail;

        Char_names char_names;

       

        /**
         * The main subgraph name in the graph.
         */
		char* main_subgraph;
        
		Line_dynamic_array<Subgraph>        subgraphs;
        
		Line_dynamic_array<External_edge>   external_edges;
        
		Line_dynamic_array<Vertex_template> vertex_templates;
        
		Line_dynamic_array<Edge_template>   edge_templates;
    };

    /**
     * This class contains links to blocks of code in C/C++ for vertices or "header", 
     * "root" and "tail" in graph.
     */
    class Code_block
    {
	protected:
        /**
         * The string contans a code for vertices in subgraphs or globals like 
         * "header", "root", "tail".
         *
         * If value is NULL you should read next field called 'file_name'.
         */   
	    char* code;
        /**
         * The string with name of file where code is written. 
         * The NULL value shows that 'code' field are used. If values of 'code'  and 'file_name' are NULL 
         * then this code block is unusable.
         */ 
        char* file_name;
    };

    class Subgraph
    {
    protected:
        frigate_name_id_type name_id;
        char* condition_code;
        int   prefefined_condition_value;
        Line_dynamic_array<Vertex> vertices;
        Line_dynamic_array<Internal_edge> internal_edges;
        Line_dynamic_array<Control_edge>  control_edges;

    };

    class External_edge
    {
    protected:
        frigate_name_id_type name_id;
        frigate_name_id_type template_name_id;
        
        /*
         * Send side 
         */

        frigate_name_id_type send_subgraph_id;
        frigate_name_id_type send_vertex_id;
        frigate_name_id_type send_exchange_block_id;

        /*
         * Recv side
         */

        frigate_name_id_type recv_subgraph_id;
        frigate_name_id_type recv_vertex_id;
        frigate_name_id_type recv_exchange_block_id;
    };


}

#endif /* __FRIGATE_GRAPH_H__ */

