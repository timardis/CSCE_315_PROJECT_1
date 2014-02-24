#ifndef UPDATE_OBJ_H
#define UPDATE_OBJ_H
#include "condition_obj.h"
class update_obj {
public:
	std::string rel_name;
	std::vector<std::pair<std::string, std::string>> attribute_values;
	condition_obj condition;

	bool operator==(const update_obj& p);

};

inline bool update_obj::operator==(const update_obj &p) {
	if (rel_name == p.rel_name &&
		attribute_values == p.attribute_values &&
		condition == p.condition) {
	
		return true;
	}
	else {
		return false;
	}
}

#endif