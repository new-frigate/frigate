#ifndef COORDS_H
#define COORDS_H

#include "../Parser/LexTag.h"
#include <string>
#include "StaticHelper.h"

#include "crossvector.h"

class Coord {
public:
	std::string subgraph;
	std::string vertex;
	std::string exchange;
	std::string edge;
	bool is_send;
	
	Coord() {
		this->subgraph = "";
		this->vertex = "";
		this->exchange = "";
		this->edge = "";
		this->is_send = false;
	}
	
	Coord(std::string subgraph, std::string vertex, std::string exchange) {
		this->subgraph = subgraph;
		this->vertex = vertex;
		this->exchange = exchange;
		this->edge = "";
		this->is_send = false;
	}
	
	Coord(std::string edge, bool is_send) {
		this->subgraph = "";
		this->vertex = "";
		this->exchange = "";
		this->edge = edge;
		this->is_send = is_send;
	}
};

class CodeBlock: public EmptyClass {
public:
	std::string io_volume;
	std::string code_volume;
	std::string code;
	
	CodeBlock() {
		this->io_volume = "";
		this->code_volume = "";
		this->code = "";
	}
	
	CodeBlock(std::string io_volume, std::string code) {
		this->io_volume = io_volume;
		this->code = code;
	}
	
	CodeBlock * setIOVolume(std::string io_volume) {
		this->io_volume = io_volume;
		return this;
	}
	
	CodeBlock * setCode(std::string code) {
		this->code = code;
		return this;
	}
	
	CodeBlock * fromFile(std::string filename) {
		this->code = StaticHelper::readFile(filename);
                return this;
	}
	
	void readTag(graph * graph, code_volume_clause * code_volume_clause) {
		if (code_volume_clause->_code_declarations != nullptr) {
			if (code_volume_clause->_code_declarations->_code_volume_weight_clause != nullptr) {
				this->code_volume = code_volume_clause->_code_declarations->_code_volume_weight_clause->value->value;
			}
			if (code_volume_clause->_code_declarations->_io_volume_weight_clause != nullptr) {
				this->io_volume = code_volume_clause->_code_declarations->_io_volume_weight_clause->value->value;
			}
		}
		if (graph->actname(code_volume_clause->value) == "StringTag") {
			this->code = StaticHelper::readFile(((StringTag *)code_volume_clause->value)->value);
		}
		else if (graph->actname(code_volume_clause->value) == "CodeClauseTag") {
			this->code = ((CodeClauseTag *)code_volume_clause->value)->value;
		}
	}
};

class Fragment {
public:
	std::string variable;
	std::string type;
	std::string left;
	std::string right;
	
	Fragment() {
		this->variable = "";
		this->type = "";
		this->left = "";
		this->right = "";
	}
	
	Fragment(std::string variable, std::string type, std::string left, std::string right) {
		this->variable = variable;
		this->type = type;
		this->left = left;
		this->right = right;
	}
	
	Fragment * setVariable(std::string variable) {
		this->variable = variable;
		return this;
	}
	
	Fragment * setType(std::string type) {
		this->type = type;
		return this;
	}
	
	Fragment * setLeft(std::string left) {
		this->left = left;
		return this;
	}
	
	Fragment * setRight(std::string right) {
		this->right = right;
		return this;
	}
	
	void readTag(graph * graph, edge_variables_fragment * edge_variables_fragment) {
		this->variable = edge_variables_fragment->_variable_name_clause->value->value;
		this->type = edge_variables_fragment->_variable_type_clause->value->value;
		this->left = edge_variables_fragment->_left_fragment_border_clause->value->value;
		this->right = edge_variables_fragment->_right_fragment_border_clause->value->value;
	}
};

#endif /* COORDS_H */

