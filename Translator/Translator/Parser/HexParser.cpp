#include "HexParser.h"

graph *parse(std::string name_of_file) {
	std::fstream ifs;
	ifs.open(name_of_file, std::fstream::in);
	std::string content = " " + std::string((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	
	Lexer lexer(&content);
	std::list<Tag *> * vector = lexer.go();

	Parser parser(vector);
	parser.go();

//	vect_print(vector);		

	if (vector->size() == 1) {
		Tag *tag = *vector->begin();
		if (tag->nameOfClass == "LexTag") {
			if (((LexTag *)tag)->name == "graph") {
				//std::cout << "OK" << std::endl;
			}
			else {
                            Exception ex;
                            ex.name = "LEX ERR";
                            ex.msg = "vector.size == 1, but last element is: [" +
                                    ((LexTag *)tag)->name +
                                    "]";
                            throw ex;
			}
		}
		else {
                    Exception ex;
                    ex.name = "LEX ERR";
                    ex.msg = "vector.size == 1, but last element type is: [" +
                            tag->nameOfClass + "]";
                    throw ex;
		}
		
	}
	else {
            Exception ex;
            ex.name = "LEX ERR";
            ex.msg = "vector.size != 1, vector entry:\n";
            for (Tag *tag : *vector) {
                if (tag->nameOfClass == "LexTag") {
                    if (((LexTag *)tag)->name == "name_clause")
                        ex.msg += ((LexTag *)tag)->name + ":\t" + ((name_clause *)tag)->value + "\n";
                    else
                        ex.msg += ((LexTag *)tag)->name + "\n";
                    
                }
                else {
                    ex.msg += tag->nameOfClass + "\n";
                }
            }
            throw ex;
	}
    return (graph *)(*vector->begin());
}

void vect_print(std::list<Tag *> *vector) {
	for (Tag * tag : *vector) {
		if (tag->nameOfClass == "LexTag")
			std::cout << ((LexTag *)tag)->name << std::endl;
		else
			std::cout << tag->nameOfClass << std::endl;
	}

}
