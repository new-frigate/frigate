//Main graph classes functions
#ifndef __FRIGATE_GRAPH_CPP__
#define __FRIGATE_GRAPH_CPP__

#include <string.h>
#include "graph.h"

namespace frigate{

CharNames Graph::Names;

int CodeBlock::setCode(char* _code)
{
	if(code == NULL && file_name == NULL)
	{
		code = new char[strlen(_code)];
		strcpy(code, _code);
		return 0;
	}
	return 1;
}

int CodeBlock::setFileName(char* filename)
{
	if(code == NULL && file_name == NULL)
	{
		file_name = new char[strlen(filename)];
		strcpy(file_name, filename);
		return 0;
	}
	return 1;
}

int Subgraph::setName(char* name)
{
	std::string str = name;
	frigate_name_id_type id = Graph::Names.register_name(str);
	if(id == -1)
		return -1;
	else
	{
		name_id = id;
		return 0;
	}
	return -1;
}

int Graph::setMainSubgraph(char* main_subgraph_name)
{
	std::string str = main_subgraph_name;
	frigate_name_id_type id = Graph::Names.register_name(str);
	if(id == -1)
		return -1;
	else
	{
		main_subgraph_id = id;
		return 0;
	}
	return -1;
}

Subgraph::Subgraph():name_id(-1), predefined_condition_value(){}

Subgraph* Subgraph::copy()
{
	Subgraph* sbgrph = new Subgraph();
	sbgrph->name_id = name_id;
	sbgrph->condition_code = condition_code;
	sbgrph->predefined_condition_value = predefined_condition_value;

	sbgrph->vertices = vertices;
	sbgrph->internal_edges = internal_edges;
	sbgrph->control_edges = control_edges;

/*	for(int i = 0; i<vertices.num_elements(); ++i)
	{
		sbgrph->vertices.add_element(vertices.get_elem(i));
	}
	for(int i = 0; i<internal_edges.num_elements(); ++i)
	{
		sbgrph->internal_edges.add_element(internal_edges.get_elem(i));
	}
	for(int i = 0; i<control_edges.num_elements(); ++i)
	{
		sbgrph->control_edges.add_element(control_edges.get_elem(i));
	}*/
	return sbgrph;
}

ExternalEdge::ExternalEdge(): 	name_id(-1), template_name_id(-1),
		send_subgraph_id(-1), send_vertex_id(-1), send_exchange_block_id(-1),
		recv_subgraph_id(-1), recv_vertex_id(-1), recv_exchange_block_id(-1) {}

ExternalEdge* ExternalEdge::copy()
{
	ExternalEdge* _ee = new ExternalEdge();
	_ee->name_id = name_id;
	_ee->template_name_id = template_name_id;
	_ee->send_subgraph_id = send_subgraph_id;
	_ee->send_vertex_id = send_vertex_id;
	_ee->send_exchange_block_id = send_exchange_block_id;
	_ee->recv_subgraph_id = recv_subgraph_id;
	_ee->recv_vertex_id = recv_vertex_id;
	_ee->recv_exchange_block_id = recv_exchange_block_id;
	return _ee;
}

Vertex* Vertex::copy()
{
	Vertex* _v = new Vertex();
	_v->name_id = name_id;
	_v->template_name_id = template_name_id;
	return _v;
}

Fragment* Fragment::copy()
{
	Fragment* _f = new Fragment();
	_f->variable = variable;
	_f->type = type;
	_f->left_border = left_border;
	_f->right_border = right_border;
	return _f;
}

ExchangeBlock* ExchangeBlock::copy()
{
	ExchangeBlock* _eb = new ExchangeBlock();
	_eb->name_id = name_id;

	_eb->send = send;
	_eb->recv = recv;

	/*
	for(int i = 0; i<send.num_elements(); ++i)
	{
		_eb->send.add_element(send.get_elem(i));
	}
	for(int i = 0; i<recv.num_elements(); ++i)
	{
		_eb->recv.add_element(recv.get_elem(i));
	}*/

	return _eb;
}

InternalEdge* InternalEdge::copy()
{
	InternalEdge* _ie = new InternalEdge();
	_ie->name_id = name_id;
	_ie->template_name_id = template_name_id;
	_ie->send_vertex_id = send_vertex_id;
	_ie->send_vertex_exchange_id = send_vertex_exchange_id;
	_ie->recv_vertex_id = recv_vertex_id;
	_ie->recv_vertex_exchange_id = recv_vertex_exchange_id;
	return _ie;
}

ControlEdge* ControlEdge::copy()
{
	ControlEdge* _ce = new ControlEdge();
	_ce->name_id = name_id;
	_ce->template_name_id = template_name_id;
	_ce->send_vertex_id = send_vertex_id;
	_ce->send_vertex_exchange_id = send_vertex_exchange_id;
	return _ce;
}

EdgeTemplate* EdgeTemplate::copy()
{
	EdgeTemplate* _et = new EdgeTemplate();
	_et->name_id = name_id;
	_et->send_fragments = send_fragments;
	_et->recv_fragments = recv_fragments;
	return _et;
}

VertexTemplate* VertexTemplate::copy()
{
	VertexTemplate* _vt = new VertexTemplate();
	_vt->name_id = name_id;
	_vt->inside_blocks = inside_blocks;
	return _vt;
}

//*******************************************************//
CodeBlock::~CodeBlock()
{
	if(code != NULL)
		delete [] code;
	if(file_name != NULL)
		delete [] file_name;
	if(io_volume != NULL)
		delete [] io_volume;
	if(code_volume != NULL)
		delete [] code_volume;
}

CodeBlock::CodeBlock(const CodeBlock& _cb)
{
	if(_cb.code != NULL)
	{
		code = new char[strlen(_cb.code)];
		strcpy(code, _cb.code);
	}
	if(file_name != NULL)
	{
		file_name = new char[strlen(_cb.file_name)];
		strcpy(file_name, _cb.file_name);
	}
	if(io_volume != NULL)
	{
		io_volume = new char[strlen(_cb.io_volume)];
		strcpy(io_volume, _cb.io_volume);
	}
	if(code_volume != NULL)
	{
		code_volume = new char[strlen(_cb.code_volume)];
		strcpy(code_volume, _cb.code_volume);
	}
}
//*******************************************************//

}

#endif //__FRIGATE_GRAPH_CPP__

