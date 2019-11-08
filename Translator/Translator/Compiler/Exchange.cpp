#include "Exchange.h"

Exchange::Exchange() {
	this->name = "";
}

Exchange * Exchange::setName(std::string name) {
	this->name = name;
	return this;
}

void Exchange::readTag(graph* graph, exchange_clause* exchange_clause) {
	this->name = exchange_clause->_name_clause->value;
	for (Tag * it : exchange_clause->_exchange_entry->value) {
		if (graph->actname(it) == "send_clause") {
			Coord tmpSend;
			tmpSend.edge = ((send_clause *)it)->value;
			tmpSend.is_send = true;
			this->exchange_coords.push_back(tmpSend);
		}
		if (graph->actname(it) == "recv_clause") {
			Coord tmpRecv;
			tmpRecv.edge = ((send_clause *)it)->value;
			tmpRecv.is_send = false;
			this->exchange_coords.push_back(tmpRecv);
		}
	}
}
