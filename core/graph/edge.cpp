//Main graph classes functions
#ifndef __FRIGATE_EDGE_CPP__
#define __FRIGATE_EDGE_CPP__

#include <string.h>
#include "edge.h"

namespace frigate{


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

int ExternalEdge::setSendCoords(char* subgraph, char* vert, char* exchange)
{
	registerName(subgraph, &send_subgraph_id);

	registerName(vert, &send_vertex_id);
	registerName(exchange, &send_exchange_block_id);
	return 0;
}

int ExternalEdge::setRecvCoords(char* subgraph, char* vert, char* exchange)
{
	registerName(subgraph, &recv_subgraph_id);
	registerName(vert, &recv_vertex_id);
	registerName(exchange, &recv_exchange_block_id);
	return 0;
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

Fragment::Fragment(char* _variable, char* _type, char* _left_border, char* _right_border)
{
	variable.setCode(_variable);
	type.setCode(_type);
	left_border.setCode(_left_border);
	right_border.setCode(_right_border);
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

int InternalEdge::setSendCoords(char* vert, char* exchange)
{
	registerName(vert, &send_vertex_id);
	registerName(exchange, &send_vertex_exchange_id);
	return 0;
}

int InternalEdge::setRecvCoords(char* vert, char* exchange)
{
	registerName(vert, &recv_vertex_id);
	registerName(exchange, &recv_vertex_exchange_id);
	return 0;
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

int ControlEdge::setSendCoords(char* vert, char* exchange)
{
	registerName(vert, &send_vertex_id);
	registerName(exchange, &send_vertex_exchange_id);
	return 0;
}

EdgeTemplate* EdgeTemplate::copy()
{
	EdgeTemplate* _et = new EdgeTemplate();
	_et->name_id = name_id;
	_et->send_fragments = send_fragments;
	_et->recv_fragments = recv_fragments;
	return _et;
}

int EdgeTemplate::setName(char* name)
{
	int id = Graph::Names.register_name(name);
	if(id == -1)
		return -1;
	name_id = id;
	return 0;
}

int EdgeTemplate::setTemplateName(char* template_name)
{
	int id = Graph::Names.search_name(template_name);
	if(id!=-1)
	{
		template_name_id = id;
		return 0;
	}
	id = Graph::Names.register_name(template_name);
	if(id == -1)
		return -1;
	template_name_id = id;
	return 0;
}

int EdgeTemplate::setSendFragments(Line_dynamic_array<Fragment>& _send_fragments)
{
	send_fragments = _send_fragments;
	return 0;
}

int EdgeTemplate::setRecvFragments(Line_dynamic_array<Fragment>& _recv_fragments)
{
	recv_fragments = _recv_fragments;
	return 0;
}

int EdgeTemplate::registerName(char* str, int* param_id)
{
	int id = Graph::Names.search_name(str);
	if(id!=-1)
	{
		*param_id = id;
		return 0;
	}
	id = Graph::Names.register_name(str);
	if(id == -1)
		return -1;
	*param_id = id;
	return 0;
}

}

#endif //__FRIGATE_EDGE_CPP__

