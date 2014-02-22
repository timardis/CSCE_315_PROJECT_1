#include "Column.h" 
  
const string& Column::get_column_name(){ 
    return column_name; 
} 
void Column::set_column_name(const string& name){ 
    column_name = name; 
  
} 
  
void Column::add_column_data(const string& data){ 
    column_data.push_back(data); 
} 
  
void Column::replace_column_data(const string& data, const int& index){ 
    column_data[index] = data; 
} 
  
vector<string>& Column::get_column_data(){ 
    return column_data; 
} 
  
void Column::delete_data(const int& index){ 
    column_data.erase(column_data.begin() + index); 
} 
const string& Column::get_column_type(){ 
    return column_type; 
} 
  
string Column::get_data_at_index(int row_index){ 
    return column_data[row_index]; 
} 
  
void Column::erase_whole_data(){ 
    column_data.clear(); 
} 
  
void Column::add_vector_data(vector<string> data_v){ 
    for(int i = 0; i < data_v.size(); i++){ 
        column_data.push_back(data_v[i]); 
    } 
} 