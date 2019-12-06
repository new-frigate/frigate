#ifndef CONTROLEDGE_H
#define CONTROLEDGE_H

#include <vector>
#include "Coords.h"

class ControlEdge {
public:
	std::string name;
	Coord send_coord;
	std::vector<Fragment> sends;
	std::vector<Fragment> recvs;
	
	ControlEdge();
	ControlEdge(std::string name, Coord send);
	ControlEdge * addSendFragment(Fragment send);
	ControlEdge * addRecvFragment(Fragment recv);
	
	void readTag(graph * graph, control_edge * control_edge);
	void emplaceParam(std::string param, std::string value);
};

#endif /* CONTROLEDGE_H */

