#ifndef EXCHANGE_H
#define EXCHANGE_H

#include "Coords.h"

class Exchange: public EmptyClass {
public:
	std::string name;
	std::vector<Coord> exchange_coords;
	
	Exchange();
	Exchange * setName(std::string name);
	Exchange * addSend(Coord send);
	Exchange * addRecv(Coord recv);
	
	void readTag(graph * graph, exchange_clause * exchange_clause);
};

#endif /* EXCHANGE_H */

