#include "Subgraph.h"

Subgraph::Subgraph() {
	this->name = "";
}

Subgraph* Subgraph::setName(std::string name) {
	this->name = name;
	return this;
}

Subgraph* Subgraph::setCondition(std::string condition) {
	this->condition = condition;
	return this;
}

Subgraph* Subgraph::addVertex(Vertex vertex) {
	this->verticies.push_back(vertex);
	return this;
}

Subgraph* Subgraph::addInternalEdge(InternalEdge edge) {
	this->internal_edges.push_back(edge);
	return this;
}

Subgraph* Subgraph::addControlEdge(ControlEdge edge) {
	this->control_edges.push_back(edge);
	return this;
}

void Subgraph::readTag(graph* graph, subgraph* subgraph) {
	this->name = subgraph->_name_clause->value;
	this->condition = subgraph->_condition_clause->value->value;
	
	for (Tag * it : subgraph->_subgraph_entry->value) {
		if (graph->actname(it) == "vertex") {
			Vertex tmpVertex;
			tmpVertex.readTag(graph, (vertex *)it);
			this->verticies.push_back(tmpVertex);
		}
		if (graph->actname(it) == "internal_edge") {
			std::string send_v = ((internal_edge *)it)->_internal_edge_send_coords->vertex;
			std::string recv_v = ((internal_edge *)it)->_internal_edge_recv_coords->vertex;
			bool is_template_send = StaticHelper::vertex_templates.find(send_v) != StaticHelper::vertex_templates.end();
			bool is_template_recv = StaticHelper::vertex_templates.find(recv_v) != StaticHelper::vertex_templates.end();
			
			if (is_template_send || is_template_recv) {
				for (Vertex &sendVert : this->verticies) {
					if ((is_template_send ? sendVert.template_name : sendVert.name) == send_v) {
						for (Vertex &recvVert : this->verticies) {
							if ((is_template_recv ? recvVert.template_name : recvVert.name) == recv_v) {
								InternalEdge tmpIE;
								tmpIE.readTag(graph, (internal_edge *)it);
								tmpIE.send_coord.vertex = sendVert.name;
								tmpIE.recv_coord.vertex = recvVert.name;
								sendVert.rebindSend(tmpIE.name, StaticHelper::autoName() + "." + tmpIE.name);
								recvVert.rebindRecv(tmpIE.name, StaticHelper::autoName() + "." + tmpIE.name);

								tmpIE.name = StaticHelper::autoName() + "." + tmpIE.name;
								this->internal_edges.push_back(tmpIE);
								StaticHelper::genNamePref();
							}
						}
					}
				}
			}
			else {	//NORMAL EDGE
				InternalEdge tmpInternalEdge;
				tmpInternalEdge.readTag(graph, (internal_edge *)it);
				this->internal_edges.push_back(tmpInternalEdge);
			}
		}
		if (graph->actname(it) == "control_edge") {
			std::string send_v = ((control_edge *)it)->_internal_edge_send_coords->vertex;
			if (StaticHelper::vertex_templates.find(send_v) != StaticHelper::vertex_templates.end()) {
					for (Vertex &sendVert : this->verticies) {
						if (sendVert.template_name == send_v) {
							ControlEdge tmpCE;
							tmpCE.readTag(graph, (control_edge *)it);
							tmpCE.send_coord.vertex = sendVert.name;
							sendVert.rebindSend(tmpCE.name, StaticHelper::autoName() + "." + tmpCE.name);

							tmpCE.name = StaticHelper::autoName() + "." + tmpCE.name;
							this->control_edges.push_back(tmpCE);
							StaticHelper::genNamePref();
						}
					}
			}
			else {	//NORMAL EDGE
				ControlEdge tmpControlEdge;
				tmpControlEdge.readTag(graph, (control_edge *)it);
				this->control_edges.push_back(tmpControlEdge);
			}
		}
	}
}
