#include <string> 
#include <vector> 
  
using namespace std; 
  
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
    const string& get_column_name(); 
    void set_column_name(const string& name); 
    void add_column_data(const string& data); 
    void replace_column_data(const string& data, const int& index); 
    const vector<string> get_column_data(); 
    string get_data_at_index(int row_index); 
    void delete_data(const int& index);  
    void erase_whole_data(); 
    const string& get_column_type(); 
    void add_vector_data(vector<string> data_v); 
}; 