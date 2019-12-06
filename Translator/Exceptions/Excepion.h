#ifndef EXCEPION_H
#define EXCEPION_H

#include <iostream>

enum ExceptionType {
	NAME_DUPLICATION,
	NAME_NOT_FOUND,
	EDGE_NOT_FOUND,
	VERTEX_NOT_FOUND,
	GRAPH_STRUCT_ERR
};

class Exception {
public:
    std::string name;
    std::string msg;
    Exception(){
        this->name = "UNKNOWN";
        this->msg = "";
    }
	
    Exception(std::string name, std::string msg) {
        this->name = name;
        this->msg = msg;
    }
	
	Exception(ExceptionType type, std::string msg) {
        this->msg = msg;
		
		switch (type) {
			case NAME_DUPLICATION:
				this->name = "NAME DUPLICATION ERR";
				break;
			case NAME_NOT_FOUND:
				this->name = "COMPONENT NOT FOUND ERR";
				break;
			case EDGE_NOT_FOUND:
				this->name = "BAD EDGE ERR";
				break;
			case VERTEX_NOT_FOUND:
				this->name = "BAD VERTEX ERR";
				break;
			case GRAPH_STRUCT_ERR:
				this->name = "GRAPH STRUCT ERR";
				break;
		}
    }
	
	void throwAndExit() {
		std::cout << this->name << std::endl;
		std::cout << this->msg << std::endl;
	}
};

#endif /* EXCEPION_H */

