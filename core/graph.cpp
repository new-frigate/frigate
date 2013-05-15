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
		printf("ohuenchik %s \n", _code);
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

int CodeBlock::setIOVolume(char* vol)
{
	io_volume = new char[strlen(vol)];
	if(io_volume == NULL)
		return -1;
	strcpy(io_volume, vol);
	return 0;
}

int CodeBlock::setCodeVolume(char* vol)
{
	code_volume = new char[strlen(vol)];
	if(code_volume == NULL)
		return -1;
	strcpy(code_volume, vol);
	return 0;
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

//Subgraph::~Subgraph()
//{
//	printf("Hello, i'm your destructor\n");
//}

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

int VertexTemplate::setName(char* name)
{
	int id = Graph::Names.register_name(name);
	if(id == -1)
		return -1;
	vt_name_id = id;
	return 0;
}

Vertex* Vertex::copy()
{
	Vertex* _v = new Vertex();
	this->deepCopy(_v);
	_v->name_id = name_id;
	_v->template_name_id = template_name_id;
	return _v;
}

int Vertex::setTemplateName(char* template_name)
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

int ExchangeBlock::addSend(char* send_name)
{
	int id = Graph::Names.search_name(send_name);
	if(id!=-1)
	{
		send.add_element(id);
		return 0;
	}
	id = Graph::Names.register_name(send_name);
	if(id == -1)
		return -1;
	send.add_element(id);
	return 0;
}

int ExchangeBlock::addRecv(char* recv_name)
{
	int id = Graph::Names.search_name(recv_name);
	if(id!=-1)
	{
		recv.add_element(id);
		return 0;
	}
	id = Graph::Names.register_name(recv_name);
	if(id == -1)
		return -1;
	recv.add_element(id);
	return 0;
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

VertexTemplate* VertexTemplate::copy()
{
	VertexTemplate* _vt = new VertexTemplate();
	_vt->vt_name_id = vt_name_id;
	_vt->inside_blocks = inside_blocks;
	return _vt;
}

void VertexTemplate::deepCopy(Vertex* child)
{
	child->vt_name_id = vt_name_id;
	child->inside_blocks = inside_blocks;
	return;
}

int VertexTemplate::setVerticeBlocks(Line_dynamic_array<VerticeBlock>& blocks)
{
	inside_blocks = blocks;
	return 0;
}


//*******************************************************//
CodeBlock::~CodeBlock()
{
	if(code != NULL)
	{
		delete [] code;
		code = NULL;
	}
	if(file_name != NULL)
	{
		delete [] file_name;
		file_name = NULL;
	}
	if(io_volume != NULL)
	{
		delete [] io_volume;
		io_volume = NULL;
	}
	if(code_volume != NULL)
	{
		delete [] code_volume;
		code_volume = NULL;
	}
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

CodeBlock& CodeBlock::operator=(const CodeBlock& _cb)
{
	if (this != &_cb)
	{
		if (code != NULL)
			delete [] code;
		if (_cb.code != NULL)
		{
			code = new char[strlen(_cb.code)];
			strcpy(code, _cb.code);
		}
		else
			code = NULL;
		if (file_name != NULL)
			delete [] file_name;
		if (_cb.file_name != NULL)
		{
			file_name = new char[strlen(_cb.file_name)];
			strcpy(file_name, _cb.file_name);
		}
		else
			file_name = NULL;
		if (io_volume != NULL)
			delete [] io_volume;
		if (_cb.io_volume != NULL)
		{
			io_volume = new char[strlen(_cb.io_volume)];
			strcpy(io_volume, _cb.io_volume);
		}
		else
			io_volume = NULL;
		if (code_volume != NULL)
			delete [] code_volume;
		if (_cb.code_volume != NULL)
		{
			code_volume = new char[strlen(_cb.code_volume)];
			strcpy(code_volume, _cb.code_volume);
		}
		else
			code_volume = NULL;
	}
	return *this;
}

CodeBlock* CodeBlock::copy()
{
	CodeBlock* tmp = new CodeBlock();
	*tmp = *this;
	return tmp;
}
//*******************************************************//

}

#endif //__FRIGATE_GRAPH_CPP__

