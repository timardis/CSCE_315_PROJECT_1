#include <cstdarg>
#include <string>
#include <vector>
#include "Column.h"

using namespace std;

class Table{
private:

	string table_name;
	vector<Column> table_columns;
	
public:
	Table(const string& name, const vector<Column>& columns){
		table_name = name;
		table_columns = columns;
		
	}

	void set_table_name(string name);
	string get_table_name();
	void delete_table_column(Column c);
	void add_to_table_column(Column c);
	vector<Column> get_table_columns();	
	
};