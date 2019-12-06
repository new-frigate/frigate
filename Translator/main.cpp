#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

#include "Parser/HexParser.h"
#include "Exceptions/Excepion.h"
#include "Compiler/Graph.h"

#include "Compiler/crossvector.h"
#include "Compiler/Coords.h"

int main(int argc, char **argv) {
	
    
    
    std::srand(time(NULL));
	
    std::string name_of_file = "";
    if (argc == 3 && std::string(argv[1]) == "-f")
        name_of_file = argv[2];
    else
        name_of_file = "../examples/test_3.grf";
	
    StaticHelper::location_prefix = name_of_file.substr(0, name_of_file.find_last_of("/") + 1);
    
    graph *lex_graph;
    std::cout << "// Parsing... ";
    try {
        lex_graph = parse(name_of_file);	
    }
    catch (Exception ex) {
        std::cout << "\n" << ex.name << std::endl;
        std::cout << ex.msg << std::endl;
        return 1;
    }
    catch (...) {
        std::cout << "ERROR" << std::endl;            
        std::cout << "Unknown error" << std::endl;
        return 1;
    }

    std::cout << "OK" << std::endl;
	
    Graph endGraph;
	
    std::cout << "// Validation... ";
    try {
            endGraph.readTag(lex_graph);
            endGraph.validate();
			endGraph.cyclic();
    }
    catch (Exception e) {
            std::cout << "\n" << e.name << std::endl;
            std::cout << e.msg << std::endl;
            return 1;
    }
    std::cout << "OK" << std::endl;
    endGraph.prettyPrint();

    return 0;
}