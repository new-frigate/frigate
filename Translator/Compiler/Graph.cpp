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
	
	tmp = graph->_graph_declarations->_parameters_clause;
	if (tmp != nullptr) {
		parameters * params = ((parameters_clause *)tmp)->value;
		for (parameter * itParam : params->value) {
			if (!StaticHelper::registerParam(itParam->varName, itParam->array)) {
				throw Exception(ExceptionType::NAME_DUPLICATION, "Parameter <" + itParam->varName + "> name duplicated");
			}
		}
	}
	/*
	//FIND ALL VERTEX TEMPLATES NAMES
	for (Tag * it : graph->_graph_entry->value) {
		if (graph->actname(it) == "vertex_template") {
			StaticHelper::vertex_templates.insert(((vertex_template *)it)->_name_clause->value);
		}
	}*/
	
	//this->findGoodPref(graph);
	
	for (Tag * it : graph->_graph_entry->value) {
		if (graph->actname(it) == "subgraph") {
			Subgraph tmpSubgraph;
			tmpSubgraph.readTag(graph, (subgraph *)it);
			this->subgraphs.push_back(tmpSubgraph);
			if (tmpSubgraph.name == graph->_main_subgraph->value) {
				this->main_subgraph = this->subgraphs.size() - 1;
			}
		}
		if (graph->actname(it) == "external_edge") {
			param_body_clause * itParams = ((external_edge *)it)->_param_body_clause;
			if (itParams != nullptr) {
				int len = -1;
				for (std::string param : itParams->value) {
					if (StaticHelper::parameters.find(param) != StaticHelper::parameters.end()) {
						if (len < 0) {
							len = StaticHelper::parameters.at(param).size();
						}
						else {
							if (StaticHelper::parameters.at(param).size() != len) {
								throw Exception("PARAMETER SIZE ERR", "Parameter <" + param + "> at ExternalEdge <" + ((external_edge *)it)->_name_clause->value + "> has different size");
							}
						}
					}
					else {
						throw Exception(ExceptionType::NAME_NOT_FOUND, "Parameter <" + param + "> at ExternalEdge <" + ((external_edge *)it)->_name_clause->value + "> not found");
					}
				}

				for (int paramInd = 0; paramInd < len; paramInd++) {
					ExternalEdge tmpEE;
					tmpEE.readTag(graph, (external_edge *)it);
					for (std::string paramName : itParams->value) {
						tmpEE.emplaceParam("%" + paramName + "%", StaticHelper::parameters.at(paramName)[paramInd]);
					}
					this->external_edges.push_back(tmpEE);
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

void Graph::cyclic() {
	for (Subgraph &it_subgraph : this->subgraphs) {
		it_subgraph.cyclic();
	}
}
/*
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
*/
void Graph::prettyPrint() {
    std::cout << "digraph " << this->version << " {" << std::endl;
    std::map<std::string, std::map<std::string, std::string> *> *sub_map = new std::map<std::string, std::map<std::string, std::string> *>();
    int ctr = 1;
    int sub_ctr = 0;
    std::cout << "  " << "v_0 [label=\"Coordinator\"];" << std::endl;
    for (Subgraph it_subgraph : this->subgraphs) {
        std::vector<std::string> *name_vec = new std::vector<std::string>();
        std::map<std::string, std::string> *name_map = new std::map<std::string, std::string>();
        (*sub_map)[it_subgraph.name] = name_map;
        for (Vertex it_vertex : it_subgraph.verticies) {
            std::string v_name = "v_"+ std::to_string(ctr);
            (*name_map)[it_vertex.name] = v_name;
            std::cout << "  " << v_name << " [label=\"" << it_vertex.name << "\"];" << std::endl;
            ctr++;
            name_vec->push_back(it_vertex.name);
        }
        std::cout << "  subgraph cluster_" << sub_ctr++ << " {" << std::endl;
        std::cout << "    style=filled;" << std::endl;
        std::cout << "    color=lightgrey;" << std::endl;
        std::cout << "    label=\"" << it_subgraph.name << "\";" << std::endl;
        std::cout << "    node [style=filled,color=white];" << std::endl;
        for (InternalEdge it_IE : it_subgraph.internal_edges) {
            std::cout << "    " << (*name_map)[it_IE.send_coord.vertex] << " -> " << (*name_map)[it_IE.recv_coord.vertex] << 
                    "[label=\"" << it_IE.name << "\"];" << std::endl;
            for (std::vector<std::string>::iterator it = name_vec->begin(); it != name_vec->end(); ++it) {
                if (*it == it_IE.recv_coord.vertex) {
                    name_vec->erase(it);
                    break;
                }
            }
        }
        std::cout << "  }" << std::endl;
//        std::cout << "  v_0 -> " << name_map->at(name_vec->at(0)) << std::endl;
        for (ControlEdge it_CE : it_subgraph.control_edges) 
            std::cout << "  " << (*name_map)[it_CE.send_coord.vertex] << " -> " << "v_0 [style=dotted, label=\"" << 
                    it_CE.name << "\"];" << std::endl; 
        
            delete name_vec;
    }
    
    for (ExternalEdge it_EE : this->external_edges) {
        std::map<std::string, std::string> *send_map = sub_map->at(it_EE.send_coord.subgraph);
        std::map<std::string, std::string> *recv_map = sub_map->at(it_EE.recv_coord.subgraph);
        std::cout << "  " << (*send_map)[it_EE.send_coord.vertex] << " -> " << (*recv_map)[it_EE.recv_coord.vertex] << 
                " [style=dotted, label=\"" << it_EE.name << "\"];" << std::endl;
    }
        
    std::cout << "}" << std::endl;
}