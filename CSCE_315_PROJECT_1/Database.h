#include <cstdarg>
#include <string>
#include <vector>
#include "Table.h"
 
using namespace std;
 
class Database{
private:
 
    vector<vector<Table>> RELATIONAL_LIST;
    vector<vector<Table>> VIEWING_LIST;
 
    enum TableType {
        VIEWING, RELATIONAL
    };
 
    // internal utility functions
    void print_table(const vector<vector<string > >& table);
    void write_table(string table_name, const vector<vector<string>>& TABLE);
 
public:
    // Query Functions
    void select(string view_name, string in_table_name, int row_index);
    void project(string view_name, string in_table_name, vector<string> attributes);
    void rename(string view_name, string in_table_name, vector<string> attributes);
    void set_union(string view_name, string table_1_name, string table_2_name);
    void set_difference(string view_name, string table_1_name, string table_2_name);
    void cross_product(string view_name, string table_1_name, string table_2_name);
     
    // Command Functions
    void exit();
    void show(string table_name);
    void create(string table_name, vector<string> attributes, vector<string> attribute_types, vector<string> keys);
    void update(string relation_name, vector<string> attribute, vector<string> data, int row_index);
    void insert_tuple(string relation_name, vector<string> tuple);
    void insert_view(string relation_name, string view_name);
    void remove(string table_name, int row_index);                  
 
    // Utility Functions
    int get_relation_index(string table_name);
    int get_view_index(string table_name);
    int get_attribute_index(TableType type, int table_index, string attribute_name);
    void update_view_name(string new_name, string old_name);
    const vector<vector<string>>& get_table(string table_name);
};