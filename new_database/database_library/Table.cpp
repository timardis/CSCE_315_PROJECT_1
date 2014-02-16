#include "Table.h" 
  
void Table::set_table_name(const string& name){ 
    table_name = name; 
} 
  
const string& Table::get_table_name(){ 
    return table_name; 
} 
  
void Table::delete_table_column(Column* c){ 
    for(unsigned int i = 0; i < table_columns.size(); i++){ 
        if(c->get_column_name() == this->table_columns[i].get_column_name()){ 
            table_columns.erase(table_columns.begin()+ i); 
            break; 
        } 
    } 
} 
  
void Table::add_to_table_column(const Column& c){ 
    table_columns.push_back(c); 
} 
  
 vector<Column>& Table:: get_table_columns(){ 
    return table_columns; 
} 
  
const vector<string>& Table::get_keys(){ 
    return keys; 
} 
  
int Table::get_size_of_col_data(){ 
    return table_columns[0].get_column_data().size(); 
} 
  
void Table::erase_row(int row_index){ 
    for(unsigned int i = 0; i < table_columns.size(); i++){ 
        table_columns[i].delete_data(row_index); 
    } 
} 
  
void Table::set_keys(const vector<string>& k){ 
    keys = k; 
} 
  
void Table::set_attributes(const vector<Column>& c){ 
    table_columns = c; 
} 
  
vector<string> Table::get_row(int row_index){ 
    vector<string> row_data; 
    for(unsigned int i = 0; i < table_columns.size(); i++){ 
        row_data.push_back(table_columns[i].get_data_at_index(row_index)); 
    } 
    return row_data; 
} 
  
void Table::put_row(vector<string>& data){ 
    for(unsigned int i = 0; i < table_columns.size(); i++){ 
        table_columns[i].add_column_data(data[i]); 
    } 
}