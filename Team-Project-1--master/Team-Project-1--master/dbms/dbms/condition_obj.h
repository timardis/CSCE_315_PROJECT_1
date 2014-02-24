#ifndef CONDITION_OBJ_H
#define CONDITION_OBJ_H
#include "conjunction_obj.h"

//an and of comparisons that can be or'ed together
class condition_obj {
public:
	std::vector<conjunction_obj> conjunctions; //|| between elements

	bool operator==(const condition_obj &c);	//overloaded boolean operator

};

inline bool condition_obj::operator==(const condition_obj& c) {	
	bool is_equal = false;
	if (conjunctions.size() != c.conjunctions.size()) {		//if two conjunctions have unequal size they cannot be equivalent
		return false;
	}
	for (int i = 0; i < conjunctions.size(); i++) {
		if (conjunctions[i] == c.conjunctions[i]) {		//go through and confirm equality for each element, when one pair fails return false
			is_equal = true;
		}
		else {
			return false;
		}
	}
	return is_equal;
}

#endif
