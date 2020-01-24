#ifndef CROSSVECTOR_H
#define CROSSVECTOR_H

#include <type_traits>
// #include <variant>
#include "../Exceptions/Excepion.h"

class EmptyClass {
public:
	bool class_id;
};

template < typename T1, typename T2, typename E = void > class crossvector;



template<class T1, class T2>
class crossvector< T1, T2,
		typename std::enable_if< std::is_base_of< EmptyClass, T1 >::value && std::is_base_of< EmptyClass, T2>::value, void >::type> {
private:
	std::vector<T1> type1s;
	std::vector<T2> type2s;
	std::vector<int> ordinal;
public:
	crossvector() {
	}
	
	void push_back(T1 value) {
		((EmptyClass *)(&value))->class_id = true;
		this->type1s.push_back(value);
		this->ordinal.push_back(this->type1s.size());
	}
	
	void push_back(T2 value) {
		((EmptyClass *)(&value))->class_id = false;
		this->type2s.push_back(value);
		this->ordinal.push_back(-this->type2s.size());
	}
	
	EmptyClass * get(int i) {
		if (i >= this->ordinal.size()) {
			throw Exception("crossvector:", "Index out of bounds");
		}
		int j = this->ordinal[i];
		if (j > 0) {
			typename std::vector<T1>::iterator it = this->type1s.begin();
			it += j - 1;
			return &(*it);
		}
		else {
			typename std::vector<T2>::iterator it = this->type2s.begin();
			it += -j - 1;
			return &(*it);
		}
	}
	
	void clear() {
		this->type1s.clear();
		this->type2s.clear();
		this->ordinal.clear();
	}
	
	int size() {
		return this->ordinal.size();
	}
};

#endif /* CROSSVECTOR_H */

