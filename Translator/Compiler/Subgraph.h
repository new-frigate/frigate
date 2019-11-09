#ifndef SUBGRAPH_H
#define SUBGRAPH_H

#include "Vertex.h"
#include "InternalEdge.h"
#include "ControlEdge.h"


class Subgraph {
public:
	std::string name;
	std::string condition;
	std::vector<Vertex> verticies;
	std::vector<InternalEdge> internal_edges;
	std::vector<ControlEdge> control_edges;
	
	Subgraph();
	Subgraph * setName(std::string name);
	Subgraph * setCondition(std::string condition);
	Subgraph * addVertex(Vertex vertex);
	Subgraph * addInternalEdge(InternalEdge edge);
	Subgraph * addControlEdge(ControlEdge edge);
	
	void readTag(graph * graph, subgraph * subgraph);
};

#endif /* SUBGRAPH_H */

