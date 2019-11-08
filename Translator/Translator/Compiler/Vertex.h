#ifndef VERTEX_H
#define VERTEX_H

#include "Exchange.h"

class Vertex {
public:
	std::string name;
	std::string template_name;
	//std::vector<CodeBlock> codeBlocks;
	//std::vector<Exchange> exchanges;
	crossvector<Exchange, CodeBlock> body;
	
	Vertex();
	Vertex * setName(std::string name);
	Vertex * addCode(CodeBlock code);
	Vertex * addExchange(Exchange exchange);
	
	void readTag(graph * graph, vertex * vertex);
	void rebindSend(std::string old, std::string new_name);
	void rebindRecv(std::string old, std::string new_name);
};

#endif /* VERTEX_H */

