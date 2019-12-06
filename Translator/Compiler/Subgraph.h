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
	
	void cyclic();
	
private:
	bool cyclic(Vertex& v, Vertex &p, std::map<std::string, InternalEdge*> * edges, std::map<std::string, Vertex*> * verts, std::map<std::string, std::set<std::string> >* parents, std::set<std::string> * cycles);
};

#endif /* SUBGRAPH_H */

