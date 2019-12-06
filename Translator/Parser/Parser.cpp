#include "Parser.h"

Parser::Parser() {
	
}

Parser::Parser(std::list<Tag *> * tags) {
	this->qu = std::vector<LexTag *>{ new comments(), new version_clause(), new main_subgraph(), new tail_clause(), new root_clause(),
			new header_clause(), new parameter(), new parameters(), new parameters_clause(), new graph_declarations(), new name_clause(), new condition_clause(), new template_name_clause(),
			new code_volume_weight_clause(), new io_volume_weight_clause(), new code_declarations(), new code_volume_clause(), new send_clause(),
			new recv_clause(), new exchange_entry(), new exchange_clause(), new variable_name_clause(), new variable_type_clause(),
			new left_fragment_border_clause(), new right_fragment_border_clause(), new edge_variables_fragment(), new edge_variables_fragments(), new edge_template(),
			new param_body_clause(),
			new vertex_body_clause(), new vertex_template(), new internal_edge_send_coords(), new internal_edge_recv_coords(), new external_edge_send_coords(),
			new external_edge_recv_coords(), new control_edge(), new internal_edge(), new external_edge(), new vertex(),
			new subgraph_entry(), new subgraph(), new graph_entry(), new graph()};
	this->tags = tags;
}

void Parser::go() {
	for (LexTag * c : this->qu) {
            c->update(this->tags);
            delete(c);
	}
}
