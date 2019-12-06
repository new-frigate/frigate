#ifndef LEXTAG
#define LEXTAG

#include <string>
#include <list>
#include <vector>
#include "Tag.h"
#include <iterator>

class LexTag : public Tag {
public:
	std::string name;
	std::vector<std::string> variations;
        
	LexTag() {
		this->nameOfClass = "LexTag";
	}

	virtual void update(std::list<Tag *> * tags) {

	}

	bool check(Tag * t, std::string n, bool b = false) {
		if (b) {
			return t->nameOfClass == n;
		}
		else {
			return actname(t) == n;
		}
	}

	bool incit(std::list<Tag *>::iterator * it, std::list<Tag *> * li) {
		if (*it != li->end()) {
			++(*it);
			if (*it != li->end()) {
				return true;
			}
			return false;
		}
		return false;
	}
        std::string actname(Tag * t) {
		if (t->nameOfClass == "LexTag")
			return ((LexTag *)t)->name;
		return t->nameOfClass;
	}

	bool smart(std::list<Tag *>::iterator * it, std::list<Tag *> * li, std::vector<std::string> arr, std::vector<Tag *> * erased) {
            std::list<Tag *>::iterator copyit = *it;
            Tag * tt;
            for (int i = 0; i < arr.size(); i++) {
                    tt = **it;
                    if (!(check(tt, arr[i]) && (i == arr.size() - 1 || incit(it, li)))) {
                            (*it) = copyit;
                            return false;
                    }
            }
            for (int i = 0; i < arr.size(); i++) {
                    erased->push_back(*copyit);
                    copyit = li->erase(copyit);
            }
            (*it) = copyit;
            return true;
	}

	bool anyof(std::list<Tag *>::iterator * it, std::list<Tag *> * li, std::vector<std::string> arr, std::vector<Tag *> * erased) {
		std::list<Tag *>::iterator copyit = *it;
		Tag * tt = **it;
		bool added = false;
		bool cont = true;
		while (cont && *it != li->end()) {
			tt = **it;
			cont = false;
			for (int i = 0; i < arr.size(); i++) {
				if (check(tt, arr[i])) {
					erased->push_back(**it);
					*it = li->erase(*it);
					cont = true;
					added = true;
					break;
				}
			}
		}
		return added;
	}
};

class comments: public LexTag {
public:
	std::vector<Tag *> value;

	comments() {
		this->name = "comments";
	}
	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		//Tag * tt;
		while (it != tags->end()) {
			//tt = *it;
			if ((*it)->nameOfClass == "CommentTag" || (*it)->nameOfClass == "WhiteSpaceTag") {
				//delete *it;
				it = tags->erase(it);
				
			}
			else
				++it;
		}
		//std::cout << tags->size() << std::endl;
	}
};

class version_clause : public LexTag {
public:
	double value;
	version_clause() {
		this->name = "version_clause";
	}

	void update(std::list<Tag *> * tags) {
		auto it = tags->begin();
		while (it != tags->end()) {
			Tag * tt = *it;
			std::list<Tag *>::iterator copyit = it;
			if (check(tt, "VersionTag") && incit(&it, tags)) {
				tt = *it;
				//if (check(tt, "comments", true) && incit(&it, tags)) {
					//tt = *it;
					if (check(tt, "AssignTag") && incit(&it, tags)) {
						tt = *it;
						//if (check(tt, "comments", true) && incit(&it, tags)) {
							//tt = *it;
							if (check(tt, "PositiveFloatTag")) {
								version_clause * newcl = new version_clause();
								newcl->value = ((PositiveFloatTag *)tt)->value;

								copyit = tags->erase(copyit);
								copyit = tags->erase(copyit);
								copyit = tags->erase(copyit);

								it = tags->insert(copyit, newcl);
							}
						//}
					}
				//}
			}
			else {
				incit(&it, tags);
			}
		}
	}
};

class main_subgraph: public LexTag {
public:
	std::string value;

	main_subgraph() {
		this->name = "main_subgraph";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"MainSubraphTag", "AssignTag", "StringTag"}, &erased)) {
				main_subgraph * newcl = new main_subgraph();
				newcl->value = ((StringTag *)erased[2])->value;
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class tail_clause: public LexTag {
public:
	Tag * value;

	tail_clause() {
		this->name = "tail_clause";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"TailBeginTag", "TailTag", "AssignTag", "StringTag", "TailEndTag"}, &erased)) {
				tail_clause * newcl = new tail_clause();
				newcl->value = erased[3];
				it = tags->insert(it, newcl);
			}
			else if (smart(&it, tags, std::vector<std::string> {"TailBeginTag", "CodeClauseTag", "TailEndTag"}, &erased)) {
				tail_clause * newcl = new tail_clause();
				newcl->value = erased[1];
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class root_clause: public LexTag {
public:
	Tag * value;

	root_clause() {
		this->name = "root_clause";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"RootBeginTag", "RootTag", "AssignTag", "StringTag", "RootEndTag"}, &erased)) {
				root_clause * newcl = new root_clause();
				newcl->value = erased[3];
				it = tags->insert(it, newcl);
			}
			else if (smart(&it, tags, std::vector<std::string> {"RootBeginTag", "CodeClauseTag", "RootEndTag"}, &erased)) {
				root_clause * newcl = new root_clause();
				newcl->value = erased[1];
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class header_clause : public LexTag {
public:
	Tag * value;

	header_clause() {
		this->name = "header_clause";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"HeaderBeginTag", "HeaderTag", "AssignTag", "StringTag", "HeaderEndTag"}, &erased)) {
				header_clause * newcl = new header_clause();
				newcl->value = erased[3];
				it = tags->insert(it, newcl);
			}
			else if (smart(&it, tags, std::vector<std::string> {"HeaderBeginTag", "CodeClauseTag", "HeaderEndTag"}, &erased)) {
				header_clause * newcl = new header_clause();
				newcl->value = erased[1];
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class parameter : public LexTag {
public:
	std::string varName;
	std::vector<std::string> array;
	
	parameter() {
		this->name = "parameter";
	}
	
	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		bool usedNewcl = false;
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"ParameterNameTag", "AssignTag", "OpenBracketTag"}, &erased)) {
				parameter * newcl = new parameter();
				usedNewcl = false;
				newcl->varName = ((ParameterNameTag *)erased[0])->value;
				erased.clear();
				if (anyof(&it, tags, std::vector<std::string> {"StringTag"}, &erased)) {
					for (Tag * itTag : erased) {
						newcl->array.push_back(((StringTag *)itTag)->value);
					}
					erased.clear();
					if (smart(&it, tags, std::vector<std::string> {"CloseBracketTag"}, &erased)) {
						usedNewcl = true;
						it = tags->insert(it, newcl);
					}
				}
				if (!usedNewcl) {
					delete newcl;
				}
			}
			incit(&it, tags);
		}
	}
};

class parameters : public LexTag {
public:
	std::vector<parameter *> value;
	
	parameters() {
		this->name = "parameters";
	}
	
	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (anyof(&it, tags, std::vector<std::string> {"parameter"}, &erased)) {
				parameters * newcl = new parameters();
				for (Tag * itTag : erased) {
					newcl->value.push_back((parameter *)itTag);
				}
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class parameters_clause : public LexTag {
public:
	parameters * value;
	
	parameters_clause() {
		this->name = "parameters_clause";
	}
	
	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"ParametersBeginTag", "parameters", "ParametersEndTag"}, &erased)) {
				parameters_clause * newcl = new parameters_clause();
				newcl->value = (parameters *)erased[1];
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class graph_declarations : public LexTag {
public:
	version_clause * _version_clause;
	header_clause * _header_clause;
	root_clause * _root_clause;
	tail_clause * _tail_clause;
	parameters_clause * _parameters_clause;


	graph_declarations() {
		this->name = "graph_declarations";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"version_clause", "header_clause", "root_clause", "tail_clause", "parameters_clause"}, &erased)) {
				graph_declarations * newcl = new graph_declarations();
				newcl->_version_clause = (version_clause *)erased[0];
				newcl->_header_clause = (header_clause *)erased[1];
				newcl->_root_clause = (root_clause *)erased[2];
				newcl->_tail_clause = (tail_clause *)erased[3];
				newcl->_parameters_clause = (parameters_clause *)erased[4];
				it = tags->insert(it, newcl);
			}else if (smart(&it, tags, std::vector<std::string> {"version_clause", "header_clause", "root_clause", "tail_clause"}, &erased)) {
				graph_declarations * newcl = new graph_declarations();
				newcl->_version_clause = (version_clause *)erased[0];
				newcl->_header_clause = (header_clause *)erased[1];
				newcl->_root_clause = (root_clause *)erased[2];
				newcl->_tail_clause = (tail_clause *)erased[3];
				newcl->_parameters_clause = nullptr;
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class name_clause : public LexTag {
public:
	std::string value;

	name_clause() {
		this->name = "name_clause";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"NameTag", "AssignTag", "StringTag"}, &erased)) {
				name_clause * newcl = new name_clause();
				newcl->value = ((StringTag *)erased[2])->value;
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class condition_clause : public LexTag {
public:
	CodeClauseTag * value;

	condition_clause() {
		this->name = "condition_clause";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"ConditionTag", "AssignTag", "CodeClauseTag"}, &erased)) {
				condition_clause * newcl = new condition_clause();
				newcl->value = ((CodeClauseTag *)erased[2]);
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class template_name_clause : public LexTag {
public:
	std::string value;

	template_name_clause() {
		this->name = "template_name_clause";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"TemplateTag", "AssignTag", "StringTag"}, &erased)) {
				template_name_clause * newcl = new template_name_clause();
				newcl->value = ((StringTag *)erased[2])->value;
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class code_volume_weight_clause : public LexTag {
public:
	CodeClauseTag * value;

	code_volume_weight_clause() {
		this->name = "code_volume_weight_clause";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"CodeVolumeTag", "AssignTag", "CodeClauseTag"}, &erased)) {
				code_volume_weight_clause * newcl = new code_volume_weight_clause();
				newcl->value = ((CodeClauseTag *)erased[2]);
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class io_volume_weight_clause : public LexTag {
public:
	CodeClauseTag * value;

	io_volume_weight_clause() {
		this->name = "io_volume_weight_clause";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"IOVolumeTag", "AssignTag", "CodeClauseTag"}, &erased)) {
				io_volume_weight_clause * newcl = new io_volume_weight_clause();
				newcl->value = ((CodeClauseTag *)erased[2]);
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class code_declarations : public LexTag {
public:
	code_volume_weight_clause * _code_volume_weight_clause;
	io_volume_weight_clause * _io_volume_weight_clause;

	code_declarations() {
		this->name = "code_declarations";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			 if (smart(&it, tags, std::vector<std::string> {"code_volume_weight_clause", "io_volume_weight_clause"}, &erased)) {
				 code_declarations * newcl = new code_declarations();
				 newcl->_code_volume_weight_clause = (code_volume_weight_clause *)erased[0];
				 newcl->_io_volume_weight_clause = (io_volume_weight_clause *)erased[1];
				 it = tags->insert(it, newcl);
			 }
			 else if (smart(&it, tags, std::vector<std::string> {"io_volume_weight_clause", "code_volume_weight_clause"}, &erased)) {
				 code_declarations * newcl = new code_declarations();
				 newcl->_code_volume_weight_clause = (code_volume_weight_clause *)erased[1];
				 newcl->_io_volume_weight_clause = (io_volume_weight_clause *)erased[0];
				 it = tags->insert(it, newcl);
			 } else if (smart(&it, tags, std::vector<std::string> {"code_volume_weight_clause"}, &erased)) {
				code_declarations * newcl = new code_declarations();
				newcl->_code_volume_weight_clause = (code_volume_weight_clause *)erased[0];
				newcl->_io_volume_weight_clause = nullptr;
				it = tags->insert(it, newcl);
			} else if (smart(&it, tags, std::vector<std::string> {"io_volume_weight_clause"}, &erased)) {
				code_declarations * newcl = new code_declarations();
				newcl->_io_volume_weight_clause = (io_volume_weight_clause *)erased[0];
				newcl->_code_volume_weight_clause = nullptr;
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class code_volume_clause : public LexTag {
public:
	code_declarations * _code_declarations;
	Tag * value;

	code_volume_clause() {
		this->name = "code_volume_clause";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"CodeBeginTag", "code_declarations", "CodeClauseTag", "CodeEndTag"}, &erased)) {
				code_volume_clause * newcl = new code_volume_clause();
				newcl->_code_declarations = (code_declarations *)erased[1];
				newcl->value = erased[2];
				it = tags->insert(it, newcl);
			} else if (smart(&it, tags, std::vector<std::string> {"CodeBeginTag", "code_declarations", "FileTag", "AssignTag", "StringTag", "CodeEndTag"}, &erased)) {
				code_volume_clause * newcl = new code_volume_clause();
				newcl->_code_declarations = (code_declarations *)erased[1];
				newcl->value = erased[4];
				it = tags->insert(it, newcl);
			} else if (smart(&it, tags, std::vector<std::string> {"CodeBeginTag", "CodeClauseTag", "CodeEndTag"}, &erased)) {
				code_volume_clause * newcl = new code_volume_clause();
				newcl->_code_declarations = nullptr;
				newcl->value = erased[1];
				it = tags->insert(it, newcl);
			} else if (smart(&it, tags, std::vector<std::string> {"CodeBeginTag", "FileTag", "AssignTag", "StringTag", "CodeEndTag"}, &erased)) {
				code_volume_clause * newcl = new code_volume_clause();
				newcl->_code_declarations = nullptr;
				newcl->value = erased[3];
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class send_clause : public LexTag {
public:
	std::string value;

	send_clause() {
		this->name = "send_clause";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"SendTag", "AssignTag", "StringTag"}, &erased)) {
				send_clause * newcl = new send_clause();
				newcl->value = ((StringTag *)erased[2])->value;
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class recv_clause : public LexTag {
public:
	std::string value;

	recv_clause() {
		this->name = "recv_clause";
	}

	void update(std::list<Tag *> * tags) {
            std::list<Tag *>::iterator it = tags->begin();
            while (it != tags->end()) {
                std::vector<Tag *> erased;
                if (smart(&it, tags, std::vector<std::string> {"RecvTag", "AssignTag", "StringTag"}, &erased)) {
                        recv_clause * newcl = new recv_clause();
                        newcl->value = ((StringTag *)erased[2])->value;
                        it = tags->insert(it, newcl);
                }
                incit(&it, tags);
            }
	}
};

class exchange_entry : public LexTag {
public:
	std::vector<Tag *> value;

	exchange_entry() {
		this->name = "exchange_entry";
	}

	void update(std::list<Tag *> * tags) {
            std::list<Tag *>::iterator it = tags->begin();
            while (it != tags->end()) {
                std::vector<Tag *> erased;
                if (anyof(&it, tags, std::vector<std::string> {"send_clause", "recv_clause"}, &erased)) {
                        exchange_entry * newcl = new exchange_entry();
                        newcl->value = erased;
                        it = tags->insert(it, newcl);
                }
                incit(&it, tags);
            }
	}
};

class exchange_clause : public LexTag {
public:
	name_clause * _name_clause;
	exchange_entry * _exchange_entry;

	exchange_clause() {
		this->name = "exchange_clause";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"ExchangeBeginTag", "name_clause", "exchange_entry", "ExchangeEndTag"}, &erased)) {
				exchange_clause * newcl = new exchange_clause();
				newcl->_name_clause = (name_clause *)erased[1];
				newcl->_exchange_entry = (exchange_entry *)erased[2];
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class variable_name_clause : public LexTag {
public:
	CodeClauseTag * value;

	variable_name_clause() {
		this->name = "variable_name_clause";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"VariableTag", "AssignTag", "CodeClauseTag"}, &erased)) {
				variable_name_clause * newcl = new variable_name_clause();
				newcl->value = (CodeClauseTag *)erased[2];
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class variable_type_clause : public LexTag {
public:
	CodeClauseTag * value;

	variable_type_clause() {
		this->name = "variable_type_clause";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"TypeTag", "AssignTag", "CodeClauseTag"}, &erased)) {
				variable_type_clause * newcl = new variable_type_clause();
				newcl->value = (CodeClauseTag *)erased[2];
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class left_fragment_border_clause : public LexTag {
public:
	CodeClauseTag * value;

	left_fragment_border_clause() {
		this->name = "left_fragment_border_clause";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"LeftTag", "AssignTag", "CodeClauseTag"}, &erased)) {
				left_fragment_border_clause * newcl = new left_fragment_border_clause();
				newcl->value = (CodeClauseTag *)erased[2];
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class right_fragment_border_clause : public LexTag {
public:
	CodeClauseTag * value;

	right_fragment_border_clause() {
		this->name = "right_fragment_border_clause";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"RightTag", "AssignTag", "CodeClauseTag"}, &erased)) {
				right_fragment_border_clause * newcl = new right_fragment_border_clause();
				newcl->value = (CodeClauseTag *)erased[2];
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class edge_variables_fragment : public LexTag {
public:
	variable_name_clause * _variable_name_clause;
	variable_type_clause * _variable_type_clause;
	left_fragment_border_clause * _left_fragment_border_clause;
	right_fragment_border_clause * _right_fragment_border_clause;

	edge_variables_fragment() {
		this->name = "edge_variables_fragment";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"FragmentBeginTag", "variable_name_clause", "variable_type_clause", "left_fragment_border_clause", "right_fragment_border_clause", "FragmentEndTag"}, &erased)) {
				edge_variables_fragment * newcl = new edge_variables_fragment();
				newcl->_variable_name_clause = (variable_name_clause *)erased[1];
				newcl->_variable_type_clause = (variable_type_clause *)erased[2];
				newcl->_left_fragment_border_clause = (left_fragment_border_clause *)erased[3];
				newcl->_right_fragment_border_clause = (right_fragment_border_clause *)erased[4];
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class edge_variables_fragments : public LexTag {
public:
	std::vector<Tag *> value;

	edge_variables_fragments() {
		this->name = "edge_variables_fragments";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (anyof(&it, tags, std::vector<std::string> {"edge_variables_fragment"}, &erased)) {
				edge_variables_fragments * newcl = new edge_variables_fragments();
				newcl->value = erased;
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class edge_template : public LexTag {
public:
	name_clause * _name_clause;
	edge_variables_fragments * send_edge_variables_fragments;
	edge_variables_fragments * recv_edge_variables_fragments;

	edge_template() {
		this->name = "edge_template";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"EdgeTemplateBeginTag", "name_clause", "SendBeginTag", "edge_variables_fragments", "SendEndTag", "RecvBeginTag", "edge_variables_fragments", "RecvEndTag", "EdgeTemplateEndTag"}, &erased)) {
				edge_template * newcl = new edge_template();
				newcl->_name_clause = (name_clause *)erased[1];
				newcl->send_edge_variables_fragments = (edge_variables_fragments *)erased[3];
				newcl->recv_edge_variables_fragments = (edge_variables_fragments *)erased[6];
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class vertex_body_clause : public LexTag {
public:
	std::vector<Tag *> value;

	vertex_body_clause() {
		this->name = "vertex_body_clause";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (anyof(&it, tags, std::vector<std::string> {"code_volume_clause", "exchange_clause"}, &erased)) {
				vertex_body_clause * newcl = new vertex_body_clause();
				newcl->value = erased;
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class param_body_clause : public LexTag {
public:
	std::vector<std::string> value;

	param_body_clause() {
		this->name = "param_body_clause";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (anyof(&it, tags, std::vector<std::string> {"UsingTag"}, &erased)) {
				param_body_clause * newcl = new param_body_clause();
				for (Tag * itTag : erased) {
					for (std::string varName : ((UsingTag *)itTag)->value) {
						newcl->value.push_back(varName);
					}
				}
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};
/*
class vertex_body_clause : public LexTag {
public:
	std::vector<Tag *> value;
	param_body_clause * using_vars;

	vertex_body_clause() {
		this->name = "vertex_body_clause";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"param_body_clause", "vertex_calc_body_clause"}, &erased)) {
				vertex_body_clause * newcl = new vertex_body_clause();
				newcl->using_vars = (param_body_clause *)erased[0];
				newcl->value = ((vertex_calc_body_clause *)erased[1])->value;
				it = tags->insert(it, newcl);
			}
			else if (smart(&it, tags, std::vector<std::string> {"vertex_calc_body_clause"}, &erased)) {
				vertex_body_clause * newcl = new vertex_body_clause();
				newcl->value = ((vertex_calc_body_clause *)erased[0])->value;
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};
 * */

class vertex_template : public LexTag {
public:
	name_clause * _name_clause;
	vertex_body_clause * _vertex_body_clause;

	vertex_template() {
		this->name = "vertex_template";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"VertexTemplateBeginTag", "name_clause", "vertex_body_clause", "VertexTemplateEndTag"}, &erased)) {
				vertex_template * newcl = new vertex_template();
				newcl->_name_clause = (name_clause *)erased[1];
				newcl->_vertex_body_clause = (vertex_body_clause *)erased[2];
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class internal_edge_send_coords : public LexTag {
public:
	std::string vertex;
	std::string exchange_region;

	internal_edge_send_coords() {
		this->name = "internal_edge_send_coords";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"SendTag", "AssignTag", "OpenBracketTag", "StringTag", "CommaTag", "StringTag", "CloseBracketTag"}, &erased)) {
				internal_edge_send_coords * newcl = new internal_edge_send_coords();
				newcl->vertex = ((StringTag *)erased[3])->value;
				newcl->exchange_region = ((StringTag *)erased[5])->value;
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class internal_edge_recv_coords : public LexTag {
public:
	std::string vertex;
	std::string exchange_region;

	internal_edge_recv_coords() {
		this->name = "internal_edge_recv_coords";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"RecvTag", "AssignTag", "OpenBracketTag", "StringTag", "CommaTag", "StringTag", "CloseBracketTag"}, &erased)) {
				internal_edge_recv_coords * newcl = new internal_edge_recv_coords();
				newcl->vertex = ((StringTag *)erased[3])->value;
				newcl->exchange_region = ((StringTag *)erased[5])->value;
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class external_edge_send_coords : public LexTag {
public:
	std::string subgraph;
	std::string vertex;
	std::string exchange_region;

	external_edge_send_coords() {
		this->name = "external_edge_send_coords";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"SendTag", "AssignTag", "OpenBracketTag", "StringTag", "CommaTag", "StringTag", "CommaTag", "StringTag", "CloseBracketTag"}, &erased)) {
				external_edge_send_coords * newcl = new external_edge_send_coords();
				newcl->subgraph = ((StringTag *)erased[3])->value;
				newcl->vertex = ((StringTag *)erased[5])->value;
				newcl->exchange_region = ((StringTag *)erased[7])->value;
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class external_edge_recv_coords : public LexTag {
public:
	std::string subgraph;
	std::string vertex;
	std::string exchange_region;

	external_edge_recv_coords() {
		this->name = "external_edge_recv_coords";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"RecvTag", "AssignTag", "OpenBracketTag", "StringTag", "CommaTag", "StringTag", "CommaTag", "StringTag", "CloseBracketTag"}, &erased)) {
				external_edge_recv_coords * newcl = new external_edge_recv_coords();
				newcl->subgraph = ((StringTag *)erased[3])->value;
				newcl->vertex = ((StringTag *)erased[5])->value;
				newcl->exchange_region = ((StringTag *)erased[7])->value;
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class control_edge : public LexTag {
public:
	name_clause * _name_clause;
	template_name_clause * _template_name_clause;
	internal_edge_send_coords * _internal_edge_send_coords;
	param_body_clause * _param_body_clause;

	control_edge() {
		this->name = "control_edge";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"ControlEdgeBeginTag", "param_body_clause", "name_clause", "template_name_clause", "internal_edge_send_coords", "ControlEdgeEndTag"}, &erased)) {
				control_edge * newcl = new control_edge();
				newcl->_param_body_clause = (param_body_clause *)erased[1];
				newcl->_name_clause = (name_clause *)erased[2];
				newcl->_template_name_clause = (template_name_clause *)erased[3];
				newcl->_internal_edge_send_coords = (internal_edge_send_coords *)erased[4];
				it = tags->insert(it, newcl);
			}
			else if (smart(&it, tags, std::vector<std::string> {"ControlEdgeBeginTag", "name_clause", "template_name_clause", "internal_edge_send_coords", "ControlEdgeEndTag"}, &erased)) {
				control_edge * newcl = new control_edge();
				newcl->_name_clause = (name_clause *)erased[1];
				newcl->_template_name_clause = (template_name_clause *)erased[2];
				newcl->_internal_edge_send_coords = (internal_edge_send_coords *)erased[3];
				newcl->_param_body_clause = nullptr;
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class internal_edge : public LexTag {
public:
	name_clause * _name_clause;
	template_name_clause * _template_name_clause;
	internal_edge_send_coords * _internal_edge_send_coords;
	internal_edge_recv_coords * _internal_edge_recv_coords;
	param_body_clause * _param_body_clause;

	internal_edge() {
		this->name = "internal_edge";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"InternalEdgeBeginTag", "param_body_clause", "name_clause", "template_name_clause", "internal_edge_send_coords", "internal_edge_recv_coords", "InternalEdgeEndTag"}, &erased)) {
				internal_edge * newcl = new internal_edge();
				newcl->_param_body_clause = (param_body_clause *)erased[1];
				newcl->_name_clause = (name_clause *)erased[2];
				newcl->_template_name_clause = (template_name_clause *)erased[3];
				newcl->_internal_edge_send_coords = (internal_edge_send_coords *)erased[4];
				newcl->_internal_edge_recv_coords = (internal_edge_recv_coords *)erased[5];
				it = tags->insert(it, newcl);
			}
			else if (smart(&it, tags, std::vector<std::string> {"InternalEdgeBeginTag", "name_clause", "template_name_clause", "internal_edge_send_coords", "internal_edge_recv_coords", "InternalEdgeEndTag"}, &erased)) {
				internal_edge * newcl = new internal_edge();
				newcl->_name_clause = (name_clause *)erased[1];
				newcl->_template_name_clause = (template_name_clause *)erased[2];
				newcl->_internal_edge_send_coords = (internal_edge_send_coords *)erased[3];
				newcl->_internal_edge_recv_coords = (internal_edge_recv_coords *)erased[4];
				newcl->_param_body_clause = nullptr;
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class external_edge : public LexTag {
public:
	name_clause * _name_clause;
	template_name_clause * _template_name_clause;
	external_edge_send_coords * _external_edge_send_coords;
	external_edge_recv_coords * _external_edge_recv_coords;
	param_body_clause * _param_body_clause;

	external_edge() {
		this->name = "external_edge";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"ExternalEdgeBeginTag", "param_body_clause", "name_clause", "template_name_clause", "external_edge_send_coords", "external_edge_recv_coords", "ExternalEdgeEndTag"}, &erased)) {
				external_edge * newcl = new external_edge();
				newcl->_param_body_clause = (param_body_clause *)erased[1];
				newcl->_name_clause = (name_clause *)erased[2];
				newcl->_template_name_clause = (template_name_clause *)erased[3];
				newcl->_external_edge_send_coords = (external_edge_send_coords *)erased[4];
				newcl->_external_edge_recv_coords = (external_edge_recv_coords *)erased[5];
				it = tags->insert(it, newcl);
			}
			else if (smart(&it, tags, std::vector<std::string> {"ExternalEdgeBeginTag", "name_clause", "template_name_clause", "external_edge_send_coords", "external_edge_recv_coords", "ExternalEdgeEndTag"}, &erased)) {
				external_edge * newcl = new external_edge();
				newcl->_name_clause = (name_clause *)erased[1];
				newcl->_template_name_clause = (template_name_clause *)erased[2];
				newcl->_external_edge_send_coords = (external_edge_send_coords *)erased[3];
				newcl->_external_edge_recv_coords = (external_edge_recv_coords *)erased[4];
				newcl->_param_body_clause = nullptr;
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class vertex : public LexTag {
public:
	name_clause * _name_clause;
	Tag * value;
	param_body_clause * _param_body_clause;

	vertex() {
		this->name = "vertex";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"VertexBeginTag", "param_body_clause", "name_clause", "template_name_clause", "VertexEndTag"}, &erased)) {
				vertex * newcl = new vertex();
				newcl->_param_body_clause = (param_body_clause *)erased[1];
				newcl->_name_clause = (name_clause *)erased[2];
				newcl->value = erased[3];
				it = tags->insert(it, newcl);
			} else if (smart(&it, tags, std::vector<std::string> {"VertexBeginTag", "param_body_clause", "name_clause", "vertex_body_clause", "VertexEndTag"}, &erased)) {
				vertex * newcl = new vertex();
				newcl->_param_body_clause = (param_body_clause *)erased[1];
				newcl->_name_clause = (name_clause *)erased[2];
				newcl->value = erased[3];
				it = tags->insert(it, newcl);
			} else if (smart(&it, tags, std::vector<std::string> {"VertexBeginTag", "name_clause", "template_name_clause", "VertexEndTag"}, &erased)) {
				vertex * newcl = new vertex();
				newcl->_name_clause = (name_clause *)erased[1];
				newcl->value = erased[2];
				newcl->_param_body_clause = nullptr;
				it = tags->insert(it, newcl);
			} else if (smart(&it, tags, std::vector<std::string> {"VertexBeginTag", "name_clause", "vertex_body_clause", "VertexEndTag"}, &erased)) {
				vertex * newcl = new vertex();
				newcl->_name_clause = (name_clause *)erased[1];
				newcl->value = erased[2];
				newcl->_param_body_clause = nullptr;
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class subgraph_entry : public LexTag {
public:
	std::vector<Tag *> value;

	subgraph_entry() {
		this->name = "subgraph_entry";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (anyof(&it, tags, std::vector<std::string> {"vertex", "internal_edge", "control_edge"}, &erased)) {
				subgraph_entry * newcl = new subgraph_entry();
				newcl->value = erased;
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class subgraph : public LexTag {
public:
	name_clause * _name_clause;
	condition_clause * _condition_clause;
	subgraph_entry * _subgraph_entry;

	subgraph() {
		this->name = "subgraph";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"SubgraphBeginTag", "name_clause", "condition_clause", "subgraph_entry", "SubgraphEndTag"}, &erased)) {
				subgraph * newcl = new subgraph();
				newcl->_name_clause = (name_clause *)erased[1];
				newcl->_condition_clause = (condition_clause *)erased[2];
				newcl->_subgraph_entry = (subgraph_entry *)erased[3];
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class graph_entry : public LexTag {
public:
	std::vector<Tag *> value;

	graph_entry() {
		this->name = "graph_entry";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (anyof(&it, tags, std::vector<std::string> {"subgraph", "external_edge", "edge_template", "vertex_template"}, &erased)) {
				graph_entry * newcl = new graph_entry();
				newcl->value = erased;
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

class graph : public LexTag {
public:
	graph_declarations * _graph_declarations;
	main_subgraph *_main_subgraph;
	graph_entry * _graph_entry;

	graph() {
		this->name = "graph";
	}

	void update(std::list<Tag *> * tags) {
		std::list<Tag *>::iterator it = tags->begin();
		while (it != tags->end()) {
			std::vector<Tag *> erased;
			if (smart(&it, tags, std::vector<std::string> {"GraphBeginTag", "graph_declarations", "main_subgraph", "graph_entry", "GraphEndTag"}, &erased)) {
				graph * newcl = new graph();
				newcl->_graph_declarations = (graph_declarations *)erased[1];
				newcl->_main_subgraph = (main_subgraph *)erased[2];
				newcl->_graph_entry = (graph_entry *)erased[3];
				it = tags->insert(it, newcl);
			}
                        else if (smart(&it, tags, std::vector<std::string> {"GraphBeginTag", "graph_declarations", "graph_entry", "GraphEndTag"}, &erased)) {
				graph * newcl = new graph();
				newcl->_graph_declarations = (graph_declarations *)erased[1];
				newcl->_main_subgraph = nullptr;
				newcl->_graph_entry = (graph_entry *)erased[3];
				it = tags->insert(it, newcl);
			}
			incit(&it, tags);
		}
	}
};

#endif
