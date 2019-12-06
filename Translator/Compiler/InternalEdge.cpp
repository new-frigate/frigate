#include <vector>

#include "InternalEdge.h"

InternalEdge::InternalEdge() {
	this->name = "";
}

InternalEdge::InternalEdge(std::string name, Coord send_coord, Coord recv_coord) {
	this->name = name;
	this->send_coord = send_coord;
	this->recv_coord = recv_coord;
}

InternalEdge* InternalEdge::addSendFragment(Fragment send) {
	this->sends.push_back(send);
	return this;
}


InternalEdge* InternalEdge::addRecvFragment(Fragment recv) {
	this->recvs.push_back(recv);
	return this;
}

void InternalEdge::readTag(graph* graph, internal_edge* internal_edge) {
	this->name = internal_edge->_name_clause->value;
	this->send_coord.vertex = internal_edge->_internal_edge_send_coords->vertex;
	this->send_coord.exchange = internal_edge->_internal_edge_send_coords->exchange_region;
	this->recv_coord.vertex = internal_edge->_internal_edge_recv_coords->vertex;
	this->recv_coord.exchange = internal_edge->_internal_edge_recv_coords->exchange_region;
	
	for (Tag * it : graph->_graph_entry->value) {
		if (graph->actname(it) == "edge_template") {
			edge_template * tmpEdge = (edge_template *)it;
			if (tmpEdge->_name_clause->value == internal_edge->_template_name_clause->value) {
				for (Tag * fragment : tmpEdge->send_edge_variables_fragments->value) {
					Fragment tmpFragment;
					tmpFragment.readTag(graph, (edge_variables_fragment *)fragment);
					this->sends.push_back(tmpFragment);
				}
				for (Tag * fragment : tmpEdge->recv_edge_variables_fragments->value) {
					Fragment tmpFragment;
					tmpFragment.readTag(graph, (edge_variables_fragment *)fragment);
					this->recvs.push_back(tmpFragment);
				}
			}
		}
	}
}

void InternalEdge::emplaceParam(std::string param, std::string value) {
	StaticHelper::replaceAll(this->name, param, value);
	
	StaticHelper::replaceAll(this->send_coord.exchange, param, value);
	StaticHelper::replaceAll(this->send_coord.vertex, param, value);
	StaticHelper::replaceAll(this->send_coord.edge, param, value);
	StaticHelper::replaceAll(this->send_coord.subgraph, param, value);
	
	StaticHelper::replaceAll(this->recv_coord.exchange, param, value);
	StaticHelper::replaceAll(this->recv_coord.vertex, param, value);
	StaticHelper::replaceAll(this->recv_coord.edge, param, value);
	StaticHelper::replaceAll(this->recv_coord.subgraph, param, value);
}

