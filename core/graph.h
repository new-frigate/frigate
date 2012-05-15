#ifndef __FRIGATE_GRAPH_H__
#define __FRIGATE_GRAPH_H__

#include <iostream>
#include <fstream>

#include "frigate_types.h"
#include "char_names.h"
#include "line_dynamic_array.h"

namespace frigate
{
//////////////////////////////
// Vertices

	/**
	 * Abstract class that must be implemented with CodeBlock or ExchangeBlock
	 */
	class VerticeBlock
	{
	public:
		virtual void toFile(std::ofstream& out) = 0;
		virtual ~VerticeBlock(){};
		virtual VerticeBlock* copy() = 0;
	};
    /**
     * This class contains links to blocks of code in C/C++ for vertices or "header", 
     * "root" and "tail" in graph.
     * Also it contains info about i/o and calculation costs.
     */
    class CodeBlock : public VerticeBlock
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

        char* io_volume;
        char* code_volume;

	public:
        CodeBlock(const CodeBlock&);
        CodeBlock():code(NULL), file_name(NULL), io_volume(NULL), code_volume(NULL){};
        int setCode(char* _code);
        int setIOVolume(char*);
        int setCodeVolume(char*);
        int setFileName(char* filename);
        void toFile(std::ofstream& out);
        CodeBlock* copy();
        ~CodeBlock();
    };

    /**
     * This class is need for possibility of multiple exchanges in one vertex
     * It contains IDs of opposite vertices
     */
    class ExchangeBlock : public VerticeBlock
    {
    protected:
    	frigate_name_id_type name_id;
    	Line_dynamic_array<frigate_name_id_type> send;
    	Line_dynamic_array<frigate_name_id_type> recv;

	public:
    	ExchangeBlock(){};
        ~ExchangeBlock(){};
        void toFile(std::ofstream& out);
        ExchangeBlock* copy();
        int addSend(char*);
        int addRecv(char*);
    };

    /**
     * Template class contains code blocks and exchange blocks
     * in arbitrary order. Every vertex must have its template
     */
    class VertexTemplate
    {
    protected:
    	frigate_name_id_type name_id;
    	Line_dynamic_array<VerticeBlock> inside_blocks;
	public:
    	VertexTemplate():name_id(-1) {}
    	VertexTemplate* copy();
    	int setName(char*);
        void toFile(std::ofstream& out);
        int setVerticeBlocks(Line_dynamic_array<VerticeBlock>&);
    };

    /**
     * Vertex class is specific vertex.
     * Several vertices may have same template
     */
    class Vertex: public VertexTemplate
    {
    protected:
    	frigate_name_id_type name_id;
    	frigate_name_id_type template_name_id;

    public:
    	Vertex():name_id(-1), template_name_id(-1){}
    	int setTemplateName(char*);
        void toFile(std::ofstream& out);
        Vertex* copy();
    };


////////////////////////////////////////////
// Edges

    /**
     * Class with data for MPI-calls in edges
     */
    class Fragment
    {
    protected:
    	CodeBlock variable;
    	CodeBlock type;
    	CodeBlock left_border;
    	CodeBlock right_border;

    public:
    	Fragment(){};
    	Fragment(char*, char*, char*, char*);
        void toFile(std::ofstream& out);
        Fragment* copy();
    };

    /*
     * Template of edge, contains information about sending and
     * receiving variables
     */
    class EdgeTemplate
    {
    protected:
    	frigate_name_id_type name_id;
    	frigate_name_id_type template_name_id;

    	Line_dynamic_array<Fragment> send_fragments;
    	Line_dynamic_array<Fragment> recv_fragments;

    public:
    	EdgeTemplate():name_id(-1) {}
    	int setName(char*);
    	EdgeTemplate* copy();
    	int setSendFragments(Line_dynamic_array<Fragment>&);
    	int setRecvFragments(Line_dynamic_array<Fragment>&);
        void toFile(std::ofstream& out);
        int setTemplateName(char*);
        static int registerName(char* str, int* param_id);
    private:
    };

    /*
     * Internal edge for subgraph contains sending and receiving vertices coords
     */
    class InternalEdge: public EdgeTemplate
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

    public:
    	InternalEdge():name_id(-1), template_name_id(-1),
    	send_vertex_id(-1), send_vertex_exchange_id(-1),
    	recv_vertex_id(-1), recv_vertex_exchange_id(-1) {}
        void toFile(std::ofstream& out);
        int setSendCoords(char*, char*);
        int setRecvCoords(char*, char*);
        InternalEdge* copy();
    };

    /*
     * Control edge always connect with control vertex
     */
    class ControlEdge: public EdgeTemplate
    {
    	frigate_name_id_type name_id;
    	frigate_name_id_type template_name_id;
    	frigate_name_id_type send_vertex_id;
    	frigate_name_id_type send_vertex_exchange_id;

    public:
    	ControlEdge():name_id(-1), template_name_id(-1),
    	send_vertex_id(-1), send_vertex_exchange_id(-1) {}
    	ControlEdge* copy();
    	int setSendCoords(char*, char*);
        void toFile(std::ofstream& out);

    };

    /*
     * External edge connect vertices in different subgraphs
     */
    class ExternalEdge: public EdgeTemplate
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

    public:
        ExternalEdge();
        void toFile(std::ofstream& out);
        int setSendCoords(char*, char*, char*);
        int setRecvCoords(char*, char*, char*);
        ExternalEdge* copy();

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
        CodeBlock condition_code;
        int   predefined_condition_value;
        Line_dynamic_array<Vertex> vertices;
        Line_dynamic_array<InternalEdge> internal_edges;
        Line_dynamic_array<ControlEdge>  control_edges;

    public:
        Subgraph();
        void toFile(std::ofstream& out);
        int setName(char*);
        void setCondition(CodeBlock& _cond){condition_code = _cond;}
        void setEntries( Line_dynamic_array<Vertex>& _vertices,
        				 Line_dynamic_array<InternalEdge>& _internal_edges,
        				 Line_dynamic_array<ControlEdge>& _control_edges)
        {
        	vertices = _vertices;
        	internal_edges = _internal_edges;
        	control_edges = _control_edges;
        }
        Subgraph* copy();
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
    public:
    	static CharNames Names;
	protected:
		float version;

		CodeBlock header;
		CodeBlock root;
		CodeBlock tail;

        /**
         * The main subgraph id in the graph.
         */
		frigate_name_id_type main_subgraph_id;

		//char* main_subgraph;

		Line_dynamic_array<Subgraph>        subgraphs;

		Line_dynamic_array<ExternalEdge>   external_edges;

		Line_dynamic_array<VertexTemplate> vertex_templates;

		Line_dynamic_array<EdgeTemplate>   edge_templates;

	public:
		void setHeader(CodeBlock& _header){header = _header;}
		void setRoot(CodeBlock& _root){root = _root;}
		void setTail(CodeBlock& _tail){tail = _tail;}
		void setVersion(float _version){version = _version;}
		int setMainSubgraph(char* main_subgraph_name);
		void setEntries( Line_dynamic_array<Subgraph>& _subgraphs,
						 Line_dynamic_array<ExternalEdge>& _external_edges,
						 Line_dynamic_array<VertexTemplate>& _vertex_templates,
						 Line_dynamic_array<EdgeTemplate>& _edge_templates )
		{
			subgraphs = _subgraphs;
			external_edges = _external_edges;
			vertex_templates = _vertex_templates;
			edge_templates = _edge_templates;
		}
		void toFile(std::ofstream& out);
		int toFile(char* filename);

    };

}

#endif /* __FRIGATE_GRAPH_H__ */

