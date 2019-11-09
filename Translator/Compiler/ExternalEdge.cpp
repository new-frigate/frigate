#include <vector>

#include "ExternalEdge.h"

ExternalEdge::ExternalEdge() {
	this->name = "";
}

ExternalEdge::ExternalEdge(std::string name, Coord send, Coord recv) {
	this->name = name;
	this->send_coord = send;
	this->recv_coord = recv;
}

ExternalEdge* ExternalEdge::addSendFragment(Fragment send) {
	this->sends.push_back(send);
	return this;
}

ExternalEdge* ExternalEdge::addRecvFragment(Fragment recv) {
	this->recvs.push_back(recv);
	return this;
}

void ExternalEdge::readTag(graph* graph, external_edge* external_edge) {
	this->name = external_edge->_name_clause->value;
	this->send_coord.subgraph = external_edge->_external_edge_send_coords->subgraph;
	this->send_coord.vertex = external_edge->_external_edge_send_coords->vertex;
	this->send_coord.exchange = external_edge->_external_edge_send_coords->exchange_region;
	this->recv_coord.subgraph = external_edge->_external_edge_recv_coords->subgraph;
	this->recv_coord.vertex = external_edge->_external_edge_recv_coords->vertex;
	this->recv_coord.exchange = external_edge->_external_edge_recv_coords->exchange_region;
	
	for (Tag * it : graph->_graph_entry->value) {
		if (graph->actname(it) == "edge_template") {
			edge_template * tmpEdge = (edge_template *)it;
			if (tmpEdge->_name_clause->value == external_edge->_template_name_clause->value) {
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
