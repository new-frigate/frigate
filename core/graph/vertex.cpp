//Main graph classes functions
#ifndef __FRIGATE_VERTEX_CPP__
#define __FRIGATE_VERTEX_CPP__

#include <string.h>
#include "vertex.h"

namespace frigate{


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

int VertexTemplate::setVerticeBlocks(Line_dynamic_array<Vertex_region>& blocks)
{
	inside_blocks = blocks;
	return 0;
}


}

#endif //__FRIGATE_VERTEX_CPP__

