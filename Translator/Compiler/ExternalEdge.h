#ifndef EXTERNALEDGE_H
#define EXTERNALEDGE_H

#include "Coords.h"

class ExternalEdge {
public:
	std::string name;
	Coord send_coord;
	Coord recv_coord;
	std::vector<Fragment> sends;
	std::vector<Fragment> recvs;
	
	ExternalEdge();
	ExternalEdge(std::string name, Coord send, Coord recv);
	
	ExternalEdge * addSendFragment(Fragment send);
	ExternalEdge * addRecvFragment(Fragment recv);
	
	void readTag(graph * graph, external_edge * external_edge);
};

#endif /* EXTERNALEDGE_H */

