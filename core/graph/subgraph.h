#ifndef __FRIGATE_SUBGRAPH_H__
#define __FRIGATE_SUBGRAPH_H__

#include "line_dynamic_array.h"
#include "code_block.h"

namespace frigate
{

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
        //~Subgraph();
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


} /* End namespace frigate */



#endif /* __FRIGATE_SUBGRAPH_H__ */

