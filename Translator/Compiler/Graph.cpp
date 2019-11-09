#include "Graph.h"

Graph::Graph() {
}

void Graph::readTag(graph* graph) {
	this->main_subgraph = -1;
	this->version = graph->_graph_declarations->_version_clause->value;
	Tag * tmp = graph->_graph_declarations->_header_clause->value;
	if (graph->actname(tmp) == "StringTag") {
		this->header = StaticHelper::readFile(((StringTag *)tmp)->value);
	}
	else {
		this->header = ((CodeClauseTag *)tmp)->value;
	}
	
	tmp = graph->_graph_declarations->_root_clause->value;
	if (graph->actname(tmp) == "StringTag") {
		this->root = StaticHelper::readFile(((StringTag *)tmp)->value);
	}
	else {
		this->root = ((CodeClauseTag *)tmp)->value;
	}
	
	tmp = graph->_graph_declarations->_tail_clause->value;
	if (graph->actname(tmp) == "StringTag") {
		this->tail = StaticHelper::readFile(((StringTag *)tmp)->value);
	}
	else {
		this->tail = ((CodeClauseTag *)tmp)->value;
	}
	
	//FIND ALL VERTEX TEMPLATES NAMES
	for (Tag * it : graph->_graph_entry->value) {
		if (graph->actname(it) == "vertex_template") {
			StaticHelper::vertex_templates.insert(((vertex_template *)it)->_name_clause->value);
		}
	}
	
	this->findGoodPref(graph);
	
	for (Tag * it : graph->_graph_entry->value) {
		if (graph->actname(it) == "subgraph") {
			Subgraph tmpSubgraph;
			try {
				tmpSubgraph.readTag(graph, (subgraph *)it);
			}
			catch (Exception e) {
				throw e;
			}
			this->subgraphs.push_back(tmpSubgraph);
			if (tmpSubgraph.name == graph->_main_subgraph->value) {
				this->main_subgraph = this->subgraphs.size() - 1;
			}
		}
		if (graph->actname(it) == "external_edge") {
			std::string send_v = ((external_edge *)it)->_external_edge_send_coords->vertex;
			std::string recv_v = ((external_edge *)it)->_external_edge_recv_coords->vertex;
			bool is_template_send = StaticHelper::vertex_templates.find(send_v) != StaticHelper::vertex_templates.end();
			bool is_template_recv = StaticHelper::vertex_templates.find(recv_v) != StaticHelper::vertex_templates.end();
			if (is_template_send || is_template_recv) {
				for (Subgraph &send_subgraph : this->subgraphs)
					for (Vertex &sendVert : send_subgraph.verticies) {
						if ((is_template_send ? sendVert.template_name : sendVert.name) == send_v) {
							for (Subgraph &recv_subgraph : this->subgraphs) {
								for (Vertex &recvVert : recv_subgraph.verticies) {
									if ((is_template_recv ? recvVert.template_name : recvVert.name) == recv_v) {
										ExternalEdge tmpEE;
										tmpEE.readTag(graph, (external_edge *)it);
										tmpEE.send_coord.vertex = sendVert.name;
										tmpEE.send_coord.subgraph = send_subgraph.name;
										tmpEE.recv_coord.vertex = recvVert.name;
										tmpEE.recv_coord.subgraph = recv_subgraph.name;
										sendVert.rebindSend(tmpEE.name, StaticHelper::autoName() + "." + tmpEE.name);
										recvVert.rebindRecv(tmpEE.name, StaticHelper::autoName() + "." + tmpEE.name);

										tmpEE.name = StaticHelper::autoName() + "." + tmpEE.name;
										this->external_edges.push_back(tmpEE);
										StaticHelper::genNamePref();
									}
								}
							}
						}
					}
			}
			else {	//NORMAL EDGE
				ExternalEdge tmpExternalEdge;
				tmpExternalEdge.readTag(graph, (external_edge *)it);
				this->external_edges.push_back(tmpExternalEdge);
			}
		}
	}
}

void Graph::validate() {
	std::set<std::string> subgraph_names;
	std::set<std::string> edge_names;
	std::set<std::string> vertex_names;
	
	for (ExternalEdge it_externalEdge : this->external_edges) {
		if (edge_names.find(it_externalEdge.name) != edge_names.end()) {
			throw Exception(ExceptionType::NAME_DUPLICATION, "ExternalEdge <" + it_externalEdge.name + "> name duplicated");
		}
		edge_names.insert(it_externalEdge.name);
	}
	
	for (Subgraph it_subgraph : this->subgraphs) {
		if (subgraph_names.find(it_subgraph.name) != subgraph_names.end()) {
			throw Exception(ExceptionType::NAME_DUPLICATION, "Subgraph name <" + it_subgraph.name + "> duplication");
		}
		subgraph_names.insert(it_subgraph.name);
		
		for (Vertex it_vertex : it_subgraph.verticies) {
			if (vertex_names.find(it_subgraph.name + "." + it_vertex.name) != vertex_names.end()) {
				throw Exception(ExceptionType::NAME_DUPLICATION, "Vertex name <" + it_vertex.name + "> in Subgraph <" + it_subgraph.name + "> duplication");
			}
			vertex_names.insert(it_subgraph.name + "." + it_vertex.name);
		}
		
		for (InternalEdge it_internalEdge : it_subgraph.internal_edges) {
			if (edge_names.find(it_internalEdge.name) != edge_names.end()) {
				throw Exception(ExceptionType::NAME_DUPLICATION, "InternalEdge <" + it_internalEdge.name + "> in Subgraph <" + it_subgraph.name + "> duplicates ExternalEdge");
			}
			if (edge_names.find(it_subgraph.name + "." + it_internalEdge.name) != edge_names.end()) {
				throw Exception(ExceptionType::NAME_DUPLICATION, "InternalEdge <" + it_internalEdge.name + "> in Subgraph <" + it_subgraph.name + "> name duplicated");
			}
			edge_names.insert(it_subgraph.name + "." + it_internalEdge.name);
		}
		
		for (ControlEdge it_controlEdge : it_subgraph.control_edges) {
			if (edge_names.find(it_controlEdge.name) != edge_names.end()) {
				throw Exception(ExceptionType::NAME_DUPLICATION, "ControlEdge <" + it_controlEdge.name + "> in Subgraph <" + it_subgraph.name + "> duplicates ExternalEdge");
			}
			if (edge_names.find(it_subgraph.name + "." + it_controlEdge.name) != edge_names.end()) {
				throw Exception(ExceptionType::NAME_DUPLICATION, "ControlEdge <" + it_controlEdge.name + "> in Subgraph <" + it_subgraph.name + "> name duplicated");
			}
			
			edge_names.insert(it_subgraph.name + "." + it_controlEdge.name);
		}
	}
	
	for (Subgraph it_subgraph : this->subgraphs) {
		for (Vertex it_vertex : it_subgraph.verticies) {
			for (int i = 0; i < it_vertex.body.size(); i++) {
				EmptyClass * it_empty = it_vertex.body.get(i);
				if (it_empty->class_id) {
					Exchange * it_exchange = (Exchange *)it_empty;
					for (Coord it_coord : it_exchange->exchange_coords) {
						if (edge_names.find(it_coord.edge) == edge_names.end()) {
							if (edge_names.find(it_subgraph.name + "." + it_coord.edge) == edge_names.end()) {
								throw Exception(ExceptionType::EDGE_NOT_FOUND, "Edge <" + it_coord.edge + "> for " + (it_coord.is_send ? "SEND" : "RECV") + " exchange <" + it_exchange->name + "> in vertex <" + it_vertex.name + "> in subgraph <" + it_subgraph.name + "> not found");
							}
						}
					}
				}
			}
		}
		
		for (InternalEdge it_IE : it_subgraph.internal_edges) {
			if (vertex_names.find(it_subgraph.name + "." + it_IE.send_coord.vertex) == vertex_names.end()) {
				throw Exception(ExceptionType::VERTEX_NOT_FOUND, "Vertex <" + it_IE.send_coord.vertex + "> in subgraph <" + it_subgraph.name + "> for SEND at internal edge <" + it_IE.name + "> not found");
			}
			if (vertex_names.find(it_subgraph.name + "." + it_IE.recv_coord.vertex) == vertex_names.end()) {
				throw Exception(ExceptionType::VERTEX_NOT_FOUND, "Vertex <" + it_IE.recv_coord.vertex + "> in subgraph <" + it_subgraph.name + "> for RECV at internal edge <" + it_IE.name + "> not found");
			}
		}
		
		for (ControlEdge it_CE : it_subgraph.control_edges) {
			if (vertex_names.find(it_subgraph.name + "." + it_CE.send_coord.vertex) == vertex_names.end()) {
				throw Exception(ExceptionType::VERTEX_NOT_FOUND, "Vertex <" + it_CE.send_coord.vertex + "> in subgraph <" + it_subgraph.name + "> for SEND at control edge <" + it_CE.name + "> not found");
			}
		}
	}
	
	for (ExternalEdge it_EE : this->external_edges) {
		if (vertex_names.find(it_EE.send_coord.subgraph + "." + it_EE.send_coord.vertex) == vertex_names.end()) {
			throw Exception(ExceptionType::VERTEX_NOT_FOUND, "Vertex <" + it_EE.send_coord.vertex + "> in subgraph <" + it_EE.send_coord.subgraph + "> for SEND at external edge <" + it_EE.name + "> not found");
		}
		if (vertex_names.find(it_EE.recv_coord.subgraph + "." + it_EE.recv_coord.vertex) == vertex_names.end()) {
			throw Exception(ExceptionType::VERTEX_NOT_FOUND, "Vertex <" + it_EE.recv_coord.vertex + "> in subgraph <" + it_EE.recv_coord.subgraph + "> for RECV at external edge <" + it_EE.name + "> not found");
		}
	}
	
	
}

void Graph::findGoodPref(graph* graph) {
	for (Tag * it : graph->_graph_entry->value) {
		if (graph->actname(it) == "external_edge") {
			if (((external_edge *)it)->_name_clause->value.rfind(StaticHelper::autoNamePref, 0) == 0) {
				StaticHelper::badPref();
				this->findGoodPref(graph);
				return;
			}
		}
		if (graph->actname(it) == "subgraph") {
			for (Tag * itt : ((subgraph *)it)->_subgraph_entry->value) {
				if (graph->actname(itt) == "internal_edge") {
					if (((internal_edge *)itt)->_name_clause->value.rfind(StaticHelper::autoNamePref, 0) == 0) {
						
						StaticHelper::badPref();
						this->findGoodPref(graph);
						return;
					}
				}
				if (graph->actname(itt) == "control_edge") {
					if (((control_edge *)itt)->_name_clause->value.rfind(StaticHelper::autoNamePref, 0) == 0) {
						StaticHelper::badPref();
						this->findGoodPref(graph);
						return;
					}
				}
			}
		}
	}
}

void Graph::prettyPrint() {
	std::cout << "Graph " << this->version << std::endl;
	for (Subgraph it_subgraph : this->subgraphs) {
		std::cout << "		Subgraph " << it_subgraph.name << "  " << it_subgraph.verticies.size() << std::endl;
		for (Vertex it_vertex : it_subgraph.verticies) {
			std::cout << "			Vertex " << it_vertex.name << std::endl;
			for (int i = 0; i < it_vertex.body.size(); i++) {
				if (it_vertex.body.get(i)->class_id) {
					Exchange * it_exchange = (Exchange *)it_vertex.body.get(i);
					for (Coord it_coord : it_exchange->exchange_coords) {
						std::cout << "				Coord " << it_coord.is_send << " <" << it_coord.edge << ">" << std::endl;
					}
				}
			}
		}
		for (InternalEdge it_IE : it_subgraph.internal_edges) {
			std::cout << "			IE " << it_IE.name << std::endl;
			std::cout << "				Send " << it_IE.send_coord.vertex << "   " << it_IE.send_coord.exchange << std::endl;
			std::cout << "				Recv " << it_IE.recv_coord.vertex << "   " << it_IE.recv_coord.exchange << std::endl;
		}
		for (ControlEdge it_CE : it_subgraph.control_edges) {
			std::cout << "			CE " << it_CE.name << std::endl;
			std::cout << "				Send " << it_CE.send_coord.vertex << "   " << it_CE.send_coord.exchange << std::endl;
		}
	}
	for (ExternalEdge it_EE : this->external_edges) {
		std::cout << "		EE " << it_EE.name << std::endl;
		std::cout << "			Send " << it_EE.send_coord.subgraph << "   " << it_EE.send_coord.vertex << "   " << it_EE.send_coord.exchange << std::endl;
		std::cout << "			Recv " << it_EE.recv_coord.subgraph << "   " << it_EE.recv_coord.vertex << "   " << it_EE.recv_coord.exchange << std::endl;
	}
}
