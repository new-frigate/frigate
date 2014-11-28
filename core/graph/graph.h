#ifndef __FRIGATE_GRAPH_H__
#define __FRIGATE_GRAPH_H__

#include "line_dynamic_array.h"
#include "code_block.h"

namespace frigate
{

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
		int toFile(const char* filename);

    };

} /* End namespace frigate */



#endif /* __FRIGATE_GRAPH_H__ */

