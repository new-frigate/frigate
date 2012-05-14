//Functions which print classes structure in text file in Frigate format

#include <typeinfo>
#include "graph.h"

namespace frigate
{

int Graph::toFile(char* filename)
{
	std::ofstream out;
	out.open(filename);
	if(!out.is_open())
	{
		printf("Error while file open\n");
		return -1;
	}
	toFile(out);
	return 0;
}

void Graph::toFile(std::ofstream& out)
{
	out << "<graph>" << std::endl;
	out << "version = " << version << std::endl;

	header.toFile(out);
	root.toFile(out);
	tail.toFile(out);
	out << "main_subgraph = \"" << Graph::Names.get_name(main_subgraph_id) << '\"' << std::endl;

	for(int i = 0; i<subgraphs.num_elements(); ++i)
		subgraphs.get_elem(i)->toFile(out);
	for(int i = 0; i<external_edges.num_elements(); ++i)
		external_edges.get_elem(i)->toFile(out);
	for(int i = 0; i<vertex_templates.num_elements(); ++i)
		vertex_templates.get_elem(i)->toFile(out);
	for(int i = 0; i<edge_templates.num_elements(); ++i)
		edge_templates.get_elem(i)->toFile(out);

	out << "</graph>" << std::endl;
	return;
}

void Subgraph::toFile(std::ofstream& out)
{
	out << "<subgraph>" << std::endl;

	out << "name = " << Graph::Names.get_name(name_id) << std::endl;
	out << "condition = ";
	condition_code.toFile(out);
	out << std::endl;
	for(int i = 0; i<vertices.num_elements(); ++i)
		vertices.get_elem(i)->toFile(out);
	for(int i = 0; i<internal_edges.num_elements(); ++i)
		internal_edges.get_elem(i)->toFile(out);
	for(int i = 0; i<control_edges.num_elements(); ++i)
		control_edges.get_elem(i)->toFile(out);

	out << "</subgraph>" << std::endl;
	return;
}

void ExternalEdge::toFile(std::ofstream& out)
{
	out << "<external_edge>" << std::endl;
	out << "name = " << Graph::Names.get_name(name_id) << std::endl;
	out << "template = " << Graph::Names.get_name(template_name_id) << std::endl;
	out << "send=(\"" << Graph::Names.get_name(send_subgraph_id) << "\" , \""
					  << Graph::Names.get_name(send_vertex_id) << "\" , \""
					  << Graph::Names.get_name(send_exchange_block_id) << "\")\n";

	out << "recv=(\"" << Graph::Names.get_name(recv_subgraph_id) << "\" , \""
					  << Graph::Names.get_name(recv_vertex_id) << "\" , \""
					  << Graph::Names.get_name(recv_exchange_block_id) << "\")\n";

	out << "</external_edge>" << std::endl;
	return;
}

void ControlEdge::toFile(std::ofstream& out)
{
	out << "<control_edge>" << std::endl;
	out << "name = " << Graph::Names.get_name(name_id) << std::endl;
	out << "template = " << Graph::Names.get_name(template_name_id) << std::endl;

	out << "send=(\"" << Graph::Names.get_name(send_vertex_id) << "\" , \""
					  << Graph::Names.get_name(send_vertex_exchange_id) << "\")\n";

	out << "</control_edge>" << std::endl;
	return;
}

void InternalEdge::toFile(std::ofstream& out)
{
	out << "<internal_edge>" << std::endl;
	out << "name = " << Graph::Names.get_name(name_id) << std::endl;
	out << "template = " << Graph::Names.get_name(template_name_id) << std::endl;
	out << "send=(\"" << Graph::Names.get_name(send_vertex_id) << "\" , \""""
					  << Graph::Names.get_name(send_vertex_exchange_id) << "\")\n";

	out << "recv=(\"" << Graph::Names.get_name(recv_vertex_id) << "\" , \""
					  << Graph::Names.get_name(recv_vertex_exchange_id) << "\")\n";

	out << "</internal_edge>" << std::endl;
	return;
}

void EdgeTemplate::toFile(std::ofstream& out)
{
	out << "<edge_template>" << std::endl;
	out << "name = " << Graph::Names.get_name(name_id) << std::endl;

	out << "<send>" << std::endl;
	for(int i = 0; i<send_fragments.num_elements(); ++i)
		send_fragments.get_elem(i)->toFile(out);
	out << "</send>" << std::endl;

	out << "<recv>" << std::endl;
	for(int i = 0; i<recv_fragments.num_elements(); ++i)
		recv_fragments.get_elem(i)->toFile(out);
	out << "</recv>" << std::endl;

	out << "</edge_template>" << std::endl;
	return;
}

void Fragment::toFile(std::ofstream& out)
{
	out << "<fragment>" << std::endl;
	out << "variable = "; variable.toFile(out);
	out << "type = "; type.toFile(out);
	out << "left = "; left_border.toFile(out);
	out << "right = "; right_border.toFile(out);
	out << "</fragment>" << std::endl;
	return;
}

void Vertex::toFile(std::ofstream& out)
{
	out << "name = " << Graph::Names.get_name(name_id) << std::endl;
	out << "template = " << Graph::Names.get_name(template_name_id) << std::endl;
	return;
}

void VertexTemplate::toFile(std::ofstream& out)
{
	out << "<vertex_template>" << std::endl;
	out << "name = " << Graph::Names.get_name(name_id) << std::endl;

	for(int i = 0; i<inside_blocks.num_elements(); ++i)
	{
		VerticeBlock** pVertBlock= (VerticeBlock**)inside_blocks.get_elem(i);
		if (typeid(*pVertBlock) == typeid(CodeBlock))
		{
			out << "<code>" << std::endl;
			(*pVertBlock)->toFile(out);
			out << "</code>" << std::endl;
		}
		else if(typeid(*pVertBlock) == typeid(ExchangeBlock))
		{
			(*pVertBlock)->toFile(out);
		}

	}

	out << "</vertex_template>" << std::endl;
	return;
}

void ExchangeBlock::toFile(std::ofstream& out)
{
	out << "<exchange>" << std::endl;
	out << "name = " << Graph::Names.get_name(name_id) << std::endl;

	for(int i = 0; i<send.num_elements(); ++i)
		out << "send = " << Graph::Names.get_name(send.get_elem(i)) << std::endl;

	for(int i = 0; i<recv.num_elements(); ++i)
		out << "recv = " << Graph::Names.get_name(recv.get_elem(i)) << std::endl;

	out << "</exchange>" << std::endl;
	return;
}

void CodeBlock::toFile(std::ofstream& out)
{
	if(io_volume != NULL)
		out << "io_volume = " << io_volume << std::endl;
	if(code_volume != NULL)
		out << "code_volume" << code_volume << std::endl;
	if(code == NULL)
	{
		out << "file = " << file_name << std::endl;
	}
	else
	{
		out << code;
	}
	return;
}

}//end namespace frigate
