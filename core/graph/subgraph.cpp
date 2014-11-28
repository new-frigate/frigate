//Main graph classes functions
#ifndef __FRIGATE_SUBGRAPH_CPP__
#define __FRIGATE_SUBGRAPH_CPP__

#include <string.h>
#include "subgraph.h"

namespace frigate{


int Subgraph::setName(char* name)
{
	std::string str = name;
	frigate_name_id_type id = Graph::Names.register_name(str);
	if(id == -1)
		return -1;
	else
	{
		name_id = id;
		return 0;
	}
	return -1;
}

Subgraph::Subgraph():name_id(-1), predefined_condition_value(){}

//Subgraph::~Subgraph()
//{
//	printf("Hello, i'm your destructor\n");
//}

Subgraph* Subgraph::copy()
{
	Subgraph* sbgrph = new Subgraph();
	sbgrph->name_id = name_id;
	sbgrph->condition_code = condition_code;
	sbgrph->predefined_condition_value = predefined_condition_value;

	sbgrph->vertices = vertices;
	sbgrph->internal_edges = internal_edges;
	sbgrph->control_edges = control_edges;

/*	for(int i = 0; i<vertices.num_elements(); ++i)
	{
		sbgrph->vertices.add_element(vertices.get_elem(i));
	}
	for(int i = 0; i<internal_edges.num_elements(); ++i)
	{
		sbgrph->internal_edges.add_element(internal_edges.get_elem(i));
	}
	for(int i = 0; i<control_edges.num_elements(); ++i)
	{
		sbgrph->control_edges.add_element(control_edges.get_elem(i));
	}*/
	return sbgrph;
}

}

#endif //__FRIGATE_SUBGRAPH_CPP__

