//Main graph classes functions
#ifndef __FRIGATE_GRAPH_CPP__
#define __FRIGATE_GRAPH_CPP__

#include <string.h>
#include "graph.h"

namespace frigate{

CharNames Graph::Names;

int Graph::setMainSubgraph(char* main_subgraph_name)
{
	std::string str = main_subgraph_name;
	frigate_name_id_type id = Graph::Names.register_name(str);
	if(id == -1)
		return -1;
	else
	{
		main_subgraph_id = id;
		return 0;
	}
	return -1;
}


}

#endif //__FRIGATE_GRAPH_CPP__

