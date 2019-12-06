#include "Vertex.h"

Vertex::Vertex() {
	this->name = "";
	this->template_name = "";
}

Vertex* Vertex::setName(std::string name) {
	this->name = name;
	return this;
}

Vertex* Vertex::addCode(CodeBlock code) {
	this->body.push_back(code);
        return this;
}

Vertex* Vertex::addExchange(Exchange exchange) {
	this->body.push_back(exchange);
	return this;
}

void Vertex::readTag(graph* graph, vertex* vertex) {
	this->name = vertex->_name_clause->value;
	
	if (graph->actname(vertex->value) == "vertex_body_clause") {
		vertex_body_clause * tmp = (vertex_body_clause *)vertex->value;
		for (Tag * it : tmp->value) {
			if (graph->actname(it) == "code_volume_clause") {
				CodeBlock tmpCodeBlock;
				tmpCodeBlock.readTag(graph, (code_volume_clause *)it);
				this->body.push_back(tmpCodeBlock);
			}
			if (graph->actname(it) == "exchange_clause") {
				Exchange tmpExchange;
				tmpExchange.readTag(graph, (exchange_clause *)it);
				this->body.push_back(tmpExchange);
			}
		}
	}
	if (graph->actname(vertex->value) == "template_name_clause") {
		template_name_clause * tmp = (template_name_clause *)vertex->value;
		this->template_name = tmp->value;
		
		bool template_found = false;
		
		for (Tag * it : graph->_graph_entry->value) {
			if (graph->actname(it) == "vertex_template") {
				vertex_template * _vertex_template = (vertex_template *)it;
				if (_vertex_template->_name_clause->value == tmp->value) {
					
					template_found = true;
					
					for (Tag * it_body : _vertex_template->_vertex_body_clause->value) {
						if (graph->actname(it_body) == "code_volume_clause") {
							CodeBlock tmpCodeBlock;
							tmpCodeBlock.readTag(graph, (code_volume_clause *)it_body);
							this->body.push_back(tmpCodeBlock);
						}
						if (graph->actname(it_body) == "exchange_clause") {
							Exchange tmpExchange;
							tmpExchange.readTag(graph, (exchange_clause *)it_body);
							this->body.push_back(tmpExchange);
						}
					}
				}
			}
		}
		
		if (!template_found) {
			throw Exception(ExceptionType::NAME_NOT_FOUND, "Vertex template <" + this->template_name + "> for vertex <" + this->name + "> not found");
		}
	}
}

void Vertex::rebindSend(std::string old, std::string new_name) {
	for (int i = 0; i < this->body.size(); i++) {
		EmptyClass * it = this->body.get(i);
		if (it->class_id) {
			Exchange * ex = (Exchange *)it;
			for (Coord &co : ex->exchange_coords) {
				if (co.is_send && co.edge == old) {
					co.edge = new_name;
				}
			}
		}
	}
}

void Vertex::rebindRecv(std::string old, std::string new_name) {
	for (int i = 0; i < this->body.size(); i++) {
		EmptyClass * it = this->body.get(i);
		if (it->class_id) {
			Exchange * ex = (Exchange *)it;
			for (Coord &co : ex->exchange_coords) {
				if (!co.is_send && co.edge == old) {
					co.edge = new_name;
				}
			}
		}
	}
}

void Vertex::emplaceParam(std::string param, std::string value) {
	StaticHelper::replaceAll(this->name, param, value);
	EmptyClass * it;
	for (int i = 0; i < this->body.size(); i++) {
		it = this->body.get(i);
		if (it->class_id) {
			Exchange * ex = (Exchange *)it;
			StaticHelper::replaceAll(ex->name, param, value);
			for (Coord &c : ex->exchange_coords) {
				StaticHelper::replaceAll(c.exchange, param, value);
				StaticHelper::replaceAll(c.vertex, param, value);
				StaticHelper::replaceAll(c.edge, param, value);
				StaticHelper::replaceAll(c.subgraph, param, value);
			}
		}
	}
}