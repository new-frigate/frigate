#ifndef __FRIGATE_GHAPH_H__
#define __FRIGATE_GHAPH_H__

#include "frigate_types.h"
#include "char_names.h"

#include "line_dynamic_array.h"


namespace frigate
{
//////////////////////////////
// Vertices

    /**
     * This class contains links to blocks of code in C/C++ for vertices or "header", 
     * "root" and "tail" in graph.
     * Also it contains info about i/o and calculation costs.
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

        int io_volume;
        int code_volume;
    };

    /**
     * This class is need for possibility of multiple exchanges in one vertex
     * It contains IDs of opposite vertices
     */
    class Exchange_block
    {
    protected:
    	frigate_name_id_type name_id;
    	Line_dynamic_array<frigate_name_type_id> send;
    	Line_dynamic_array<frigate_name_type_id> recv;
    };

    /**
     * Template class contains code blocks and exchange blocks
     * in arbitrary order. Every vertex must have its template
     */
    class Vertex_template
    {
    protected:
    	frigate_name_id_type template_name_id;
    	Line_dynamic_array<Code_block> code_blocks;		//Need to think about
    	Line_dynamic_array<Exchange_block> exchanges;	//alternating them
    };

    /**
     * Vertex class is specific vertex.
     * Several vertices may have same template
     */
    class Vertex: public Vertex_template
    {
    protected:
    	frigate_name_id_type name_id;
    };


////////////////////////////////////////////
// Edges

    /**
     * Class with data for MPI-calls in edges
     */
    class Fragment
    {
    protected:
    	char* variable;
    	char* type;
    	char* left_border;
    	char* right_border;
    };

    /*
     * Template of edge, contains information about sending and
     * receiving variables
     */
    class Edge_template
    {
    protected:
    	frigate_name_id_type template_name_id;

    	Line_dynamic_array<Fragment> send_fragments;
    	Line_dynamic_array<Fragment> recv_fragments;
    };

    /*
     * Internal edge for subgraph contains sending and receiving vertices coords
     */
    class Internal_edge: public Edge_template
    {
    	frigate_name_id_type name_id;
    	frigate_name_id_type template_name_id;

    	/*
    	 * Send side
    	 */
    	frigate_name_id_type send_vertex_id;
    	frigate_name_id_type send_vertex_exchange_id;

    	/*
    	 * Recv side
    	 */
    	frigate_name_id_type recv_vertex_id;
    	frigate_name_id_type recv_vertex_exchange_id;
    };

    /*
     * Control edge always connect with control vertex
     */
    class Control_edge: public Edge_template
    {
    	frigate_name_id_type name_id;
    	frigate_name_id_type template_name_id;
    	frigate_name_id_type send_vertex_id;
    	frigate_name_id_type send_vertex_exchange_id;
    };

    /*
     * External edge connect vertices in different subgraphs
     */
    class External_edge: public Edge_template
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

////////////////////////////////
// Subgraphs and graph

    /*
     * Subgraph class contains vertices, internal and control edges.
     * Condition_code - some condition to start subgraph calculation
     */
    class Subgraph
    {
    protected:
        frigate_name_id_type name_id;
        char* condition_code;
        int   predefined_condition_value;
        Line_dynamic_array<Vertex> vertices;
        Line_dynamic_array<Internal_edge> internal_edges;
        Line_dynamic_array<Control_edge>  control_edges;

    };

    /*
     * Graph class contains code blocks for
     * header - some necessary includes
     * root - code for execution before any other code (initialization etc.)
     * tail - code for execution after any other code (cleaning etc.)
     * subgraphs, external edges, vertex templates and edges templates
     */
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

}

#endif /* __FRIGATE_GRAPH_H__ */

