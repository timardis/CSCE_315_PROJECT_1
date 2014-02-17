#include "Column.h" 
#include "Tuple.h"

using namespace std; 
  
class Table{ 
private: 
  
    string table_name; 
    vector<Column> table_columns; 
    vector<string> keys; 
    

public: 
    Table(const string& name, const vector<Column>& columns, const vector<string>& k){ 
        table_name = name; 
        table_columns = columns; 
        keys = k; 
          
    } 
    Table(const string& name, const vector<Column>& columns){ 
        table_name = name; 
        table_columns = columns; 
        //keys = NULL; 
          
    } 
  
    Tuple                   get_tuple(int index);

    void                    set_keys(const vector<string>& k); 
    void                    set_attributes(const vector<Column>& c); 
    void                    set_table_name(const string& name); 
    const string&           get_table_name(); 
    void                    delete_table_column(Column* c); 
    void                    add_to_table_column(const Column& c); 
    int                     get_size_of_col_data(); 
    vector<Column>&         get_table_columns();   
    const vector<string>&   get_keys(); 
    void                    erase_row(int row_index); 
    vector<string>          get_row(int row_index); 
    void                    put_row(vector<string>& data); 
};