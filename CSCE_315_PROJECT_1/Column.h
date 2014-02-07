#include <cstdarg>
#include <string>
#include <vector>

class Column{
private:
	string column_name;
	string column_type;
	vector<string> column_data;
	
public:
	Column(const string& name, const string& type){
		column_name = name;
		column_type = type;
	}
	void add_column_data(string data);
	vector<string> get_column_data();
	void delete_data(string data);	
};

