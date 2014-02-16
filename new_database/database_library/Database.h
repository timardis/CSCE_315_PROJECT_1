#ifndef DATABASE_H
#define DATABASE_H

#include <string> 
#include <vector> 
#include "Table.h" 
   
using namespace std; 
   
class Database{ 
private: 
   
    vector<Table> RELATIONAL_LIST; 
    vector<Table> VIEWING_LIST; 
   
    // internal utility functions 
    void print_table(Table& t); 
   
public: 
    // Query Functions 
    Table select(string view_name, string in_table_name, int row_index); 
    Table project(string view_name, string in_table_name, vector<string> attributes); 
    Table rename(string view_name, string in_table_name, vector<string> attributes); 
    Table set_union(string view_name, string table_1_name, string table_2_name); 
    Table set_difference(string view_name, string table_1_name, string table_2_name); 
    Table cross_product(string view_name, string table_1_name, string table_2_name); 
    Table join(string view_name, string table_1_name, string table_2_name); 
  
       
    // Command Functions 
    //void exit(); 
    void show(string table_name); 
    void create(string table_name, vector<string> attributes, vector<string> attribute_types, vector<string> keys); 
    void update(string relation_name, vector<string> attribute, vector<string> data, int row_index); 
    void insert_tuple(string relation_name, vector<string> tuple); 
    void insert_view(string relation_name, string view_name); 
    void remove(string table_name, int row_index);   
    void remove_table(string table_name); 
	  void rename_column(string table_name, string column_old_name, string column_new_name);
   
    // Utility Functions 
    int get_relation_index(string table_name); 
    int get_view_index(string table_name); 
    int get_attribute_index(Table& type, string attribute_name); 
    void update_view_name(string new_name, string old_name); 
    void update_table_name(string new_name, string old_name); 
    Table& get_table(string table_name); 
};

#endif
