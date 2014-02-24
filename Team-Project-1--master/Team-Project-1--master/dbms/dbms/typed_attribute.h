#include <vector>
#include <string>

class typed_attribute {
public:
	std::vector<std::string> list;
	std::vector<std::pair<int, int>> types; //<1, int> means type varchar of length int, <2, 0> means type integer
	//first int specifies type of variable, second specifies length assuming its a string
};