#ifndef __FRIGATE_EDGE_H__
#define __FRIGATE_EDGE_H__

#include "line_dynamic_array.h"
#include "code_block.h"

namespace frigate
{

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


} /* End namespace frigate */



#endif /* __FRIGATE_EDGE_H__ */

