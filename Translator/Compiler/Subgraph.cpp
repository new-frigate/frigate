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
			param_body_clause * itParams = ((vertex *)it)->_param_body_clause;
			if (itParams != nullptr) {
				int len = -1;
				for (std::string param : itParams->value) {
					if (StaticHelper::parameters.find(param) != StaticHelper::parameters.end()) {
						if (len < 0) {
							len = StaticHelper::parameters.at(param).size();
						}
						else {
							if (StaticHelper::parameters.at(param).size() != len) {
								throw Exception("PARAMETER SIZE ERR", "Parameter <" + param + "> at Vertex <" + ((vertex *)it)->_name_clause->value + "> has different size");
							}
						}
					}
					else {
						throw Exception(ExceptionType::NAME_NOT_FOUND, "Parameter <" + param + "> at Vertex <" + ((vertex *)it)->_name_clause->value + "> not found");
					}
				}
				
				for (int paramInd = 0; paramInd < len; paramInd++) {
					Vertex tmpVertex;
					tmpVertex.readTag(graph, (vertex *)it);
					for (std::string paramName : itParams->value) {
						tmpVertex.emplaceParam("%" + paramName + "%", StaticHelper::parameters.at(paramName)[paramInd]);
					}
					this->verticies.push_back(tmpVertex);
				}
			}
			else {
				Vertex tmpVertex;
				tmpVertex.readTag(graph, (vertex *)it);
				this->verticies.push_back(tmpVertex);
			}
		}
		if (graph->actname(it) == "internal_edge") {
			param_body_clause * itParams = ((internal_edge *)it)->_param_body_clause;
			if (itParams != nullptr) {
				int len = -1;
				for (std::string param : itParams->value) {
					if (StaticHelper::parameters.find(param) != StaticHelper::parameters.end()) {
						if (len < 0) {
							len = StaticHelper::parameters.at(param).size();
						}
						else {
							if (StaticHelper::parameters.at(param).size() != len) {
								throw Exception("PARAMETER SIZE ERR", "Parameter <" + param + "> at InternalEdge <" + ((internal_edge *)it)->_name_clause->value + "> has different size");
							}
						}
					}
					else {
						throw Exception(ExceptionType::NAME_NOT_FOUND, "Parameter <" + param + "> at InternalEdge <" + ((internal_edge *)it)->_name_clause->value + "> not found");
					}
				}

				for (int paramInd = 0; paramInd < len; paramInd++) {
					InternalEdge tmpIE;
					tmpIE.readTag(graph, (internal_edge *)it);
					for (std::string paramName : itParams->value) {
						tmpIE.emplaceParam("%" + paramName + "%", StaticHelper::parameters.at(paramName)[paramInd]);
					}
					this->internal_edges.push_back(tmpIE);
				}
			}
			else {	//NORMAL EDGE
				InternalEdge tmpInternalEdge;
				tmpInternalEdge.readTag(graph, (internal_edge *)it);
				this->internal_edges.push_back(tmpInternalEdge);
			}
		}
		if (graph->actname(it) == "control_edge") {
			param_body_clause * itParams = ((control_edge *)it)->_param_body_clause;
			if (itParams != nullptr) {
				int len = -1;
				for (std::string param : itParams->value) {
					if (StaticHelper::parameters.find(param) != StaticHelper::parameters.end()) {
						if (len < 0) {
							len = StaticHelper::parameters.at(param).size();
						}
						else {
							if (StaticHelper::parameters.at(param).size() != len) {
								throw Exception("PARAMETER SIZE ERR", "Parameter <" + param + "> at ControlEdge <" + ((control_edge *)it)->_name_clause->value + "> has different size");
							}
						}
					}
					else {
						throw Exception(ExceptionType::NAME_NOT_FOUND, "Parameter <" + param + "> at ControlEdge <" + ((control_edge *)it)->_name_clause->value + "> not found");
					}
				}

				for (int paramInd = 0; paramInd < len; paramInd++) {
					ControlEdge tmpCE;
					tmpCE.readTag(graph, (control_edge *)it);
					for (std::string paramName : itParams->value) {
						tmpCE.emplaceParam("%" + paramName + "%", StaticHelper::parameters.at(paramName)[paramInd]);
					}
					this->control_edges.push_back(tmpCE);
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

void Subgraph::cyclic() {
	std::map<std::string, InternalEdge*> * edges = new std::map<std::string, InternalEdge*>;
	std::map<std::string, Vertex*> * verts = new std::map<std::string, Vertex*>;
	std::map<std::string, std::set<std::string> >* parents = new std::map<std::string, std::set<std::string> >;
	//std::set<std::string> * cycles = new std::set<std::string>;
	
	for (InternalEdge &it_IE : this->internal_edges) {
		(*edges)[it_IE.name] = &it_IE;
	}
	int count = 0;
	std::vector<Vertex *> starts;
	for (Vertex &it_V : this->verticies) {
		(*verts)[it_V.name] = &it_V;
		bool isStart = true;
		for (int i = 0; i < it_V.body.size() && isStart; i++) {
			EmptyClass * ec = it_V.body.get(i);
			if (ec->class_id) {
				Exchange * ex = (Exchange *)ec;
				for (Coord &c : ex->exchange_coords) {
					if (!c.is_send) {
						isStart = false;
						break;
					}
				}
			}
		}
		if (isStart) {
			count++;
			starts.push_back(&it_V);
		}
	}
	if (count == 0) {
		throw Exception(ExceptionType::GRAPH_STRUCT_ERR, "Subgraph <" + this->name + "> has no initial Vertex");
	}
	
	for (Vertex * start : starts) {
		try {
			cyclic(*start, *start, edges, verts, parents, "<" + (*start).name + ">");
		}
		catch (Exception ex) {
			delete edges;
			delete verts;
			delete parents;
			throw ex;
		}
	}
	/*
	if (ret) {
		std::string names = "";
		for (std::string vert : *cycles) {
			names += vert + ", ";
		}
		names = names.substr(0, names.size() - 2);
		Exception exception(ExceptionType::GRAPH_STRUCT_ERR, "Subgraph <" + this->name + "> has cycles at vertices: " + names);
		
		delete edges;
		delete verts;
		delete parents;
		//delete cycles;
		
		throw exception;
	}
	*/
	delete edges;
	delete verts;
	delete parents;
	//delete cycles;
}

bool Subgraph::cyclic(Vertex& v, Vertex &p, std::map<std::string, InternalEdge*> * edges, std::map<std::string, Vertex*> * verts, std::map<std::string, std::set<std::string> >* parents, std::string chain) {
	if ((*parents)[v.name].count(p.name)) {
		chain + " -> <" + v.name + ">";
		chain = chain.substr(chain.find("<" + p.name + ">", 0), chain.size() - 1);
		throw Exception(ExceptionType::GRAPH_STRUCT_ERR, "Subgraph <" + this->name + "> has cycle: " + chain);
	}
	(*parents)[v.name].insert(p.name);
	for (int i = 0; i < v.body.size(); i++) {
		EmptyClass * ec = v.body.get(i);
		if (ec->class_id) {
			Exchange * ex = (Exchange *)ec;
			for (Coord &c : ex->exchange_coords) {
				if (c.is_send) {
					if ((*edges).count(c.edge) > 0) {
						InternalEdge *ie = (*edges)[c.edge];
						Vertex &tmp_v = *((*verts)[ie->recv_coord.vertex]);
						if (cyclic(tmp_v, v, edges, verts, parents, chain + " -> <" + tmp_v.name + ">")) {
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

