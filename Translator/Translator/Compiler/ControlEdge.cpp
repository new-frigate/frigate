#include "ControlEdge.h"

ControlEdge::ControlEdge() {
	this->name = "";
}

ControlEdge::ControlEdge(std::string name, Coord send) {
	this->name = name;
	this->send_coord = send;
}

ControlEdge* ControlEdge::addSendFragment(Fragment send) {
	this->sends.push_back(send);
	return this;
}

ControlEdge* ControlEdge::addRecvFragment(Fragment recv) {
	this->recvs.push_back(recv);
	return this;
}

void ControlEdge::readTag(graph* graph, control_edge* control_edge) {
	this->name = control_edge->_name_clause->value;
	this->send_coord.vertex = control_edge->_internal_edge_send_coords->vertex;
	this->send_coord.exchange = control_edge->_internal_edge_send_coords->exchange_region;
	
	for (Tag * it : graph->_graph_entry->value) {
		if (graph->actname(it) == "edge_template") {
			edge_template * tmpEdge = (edge_template *)it;
			if (tmpEdge->_name_clause->value == control_edge->_template_name_clause->value) {
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
