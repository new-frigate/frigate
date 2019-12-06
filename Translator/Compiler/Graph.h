#ifndef GRAPH_H
#define GRAPH_H

#include "../Parser/LexTag.h"
#include "Subgraph.h"
#include "ExternalEdge.h"
#include <set>

class Graph {
private:
	void findGoodPref(graph * graph);
public:
	double version;
	std::string header;
	std::string root;
	std::string tail;
	
	int main_subgraph;
	
	std::vector<Subgraph> subgraphs;
	std::vector<ExternalEdge> external_edges;
	Graph();
	
	void readTag(graph * graph);
	
	void validate();
	
	void cyclic();
	
	void prettyPrint();
};

#endif /* GRAPH_H */

