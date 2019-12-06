#ifndef INTERNALEDGE_H
#define INTERNALEDGE_H

#include "Coords.h"

class InternalEdge {
public:
	std::string name;
	Coord send_coord;
	Coord recv_coord;
	std::vector<Fragment> sends;
	std::vector<Fragment> recvs;
	
	InternalEdge();
	
	InternalEdge(std::string name, Coord send_coord, Coord recv_coord);
	
	InternalEdge * addSendFragment(Fragment send);
	InternalEdge * addRecvFragment(Fragment recv);
	
	void readTag(graph * graph, internal_edge * internal_edge);
	void emplaceParam(std::string param, std::string value);
};

#endif /* INTERNALEDGE_H */

