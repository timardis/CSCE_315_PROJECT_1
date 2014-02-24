#include "Database.h" 
#include <fstream> 
   
#include <cctype> 
#include <iostream> 
#include <iomanip> 
#include <stdexcept> 
   
/*------------------------------------------------------------------------------------*/
/* QUERY FUNCTIONS */
/*------------------------------------------------------------------------------------*/
Table Database::select(string view_name, string in_table_name, Condition& c){ 
    //check to see if view_name exists
  bool target_table_is_in_relation_list = false;

	int target_index = get_view_index(view_name);
	if(target_index >= 0){
		remove_view_table(view_name);
	}
  else if(target_index == -1)
  {
    int target_index = get_relation_index(view_name);
	  if(target_index >= 0){
		  remove_relation_table(view_name);
      target_table_is_in_relation_list = true;
	  }
  }
  else
    throw runtime_error("Invalid get_view_index() return value");

	//check to see if the other table to select from exists
  bool from_viewing_list;
  bool from_relation_list;

	int list_index = get_relation_index(in_table_name);
	
  if(list_index == -1){
    from_relation_list = false;
    list_index = get_view_index(in_table_name);
		if(list_index == -1)
    {
      from_viewing_list = false;
      throw runtime_error("Table to select() from doesn't exist");
    }
    else
      from_viewing_list = true;
	}
  else
  {
    from_relation_list = true;
    from_viewing_list = false;
  }


  Table table_copy;

  if(from_relation_list)
  {
	  table_copy = relational_list[list_index];
  }
  else if(from_viewing_list)
  {
    table_copy = viewing_list[list_index];
  }

  vector<Column> col = table_copy.get_table_columns();
  for(int i = 0; i < col.size() ; i++){
		col[i].erase_whole_data();
	}

	Table new_table(view_name, col, table_copy.get_keys());

  for(int i = 0; i < table_copy.get_size_of_col_data(); i++){
		Tuple row_tup = table_copy.get_tuple(i);
		bool b = c.evaluate_tuple(row_tup);
		if(b){
      //tuple satisfies the condition
      vector<string> selected_row = table_copy.get_row(i);
      new_table.put_row(selected_row);
		}
	}
  

  if(target_table_is_in_relation_list)
  {
    relational_list.push_back(new_table);
  }
  else
  {
	  viewing_list.push_back(new_table);
  }
	return new_table;
} 
  
Table Database::project(string view_name, string in_table_name, vector<string> attributes){ 
	Table* t1 = NULL;
	//check if the table exists already in view list
	if (view_name == in_table_name)
		throw runtime_error("Project: both name equal");
	int index = get_relation_index(in_table_name);
	Table* temp_view_table = NULL;
	vector<Column> columns;

	if (index == -1){
		//throws an error if the table doesn't exist in relational table
		index = get_view_index(in_table_name);
		if (index == -1)
			throw runtime_error("Project: no such view exists");

		else{
			bool attribute_check = false;
			//if the attributes of viewing list already exists as the attributes of before, it means,
			//attributes exists
			for (unsigned int i = 0; i<attributes.size(); i++){
				for (unsigned int j = 0; j<viewing_list[index].get_table_columns().size(); j++)
				if (attributes[i] == viewing_list[index].get_table_columns()[j].get_column_name()){
					columns.push_back(viewing_list[index].get_table_columns()[j]);
					attribute_check = true;
					break;
				}
				//if attributes do not exist correctly, throw an error
				if (attribute_check == false)
					throw runtime_error("Project: no such attribute exists (" + attributes[i] + ")");
			}

			Table t(view_name, columns);
			viewing_list.push_back(t);
			temp_view_table = &t;
		}
	}
	else{

		//checks for attribute check again and throws an error if it doesn't exist
		bool attribute_check = false;
		for (unsigned int i = 0; i<attributes.size(); i++){
			for (unsigned int j = 0; j<relational_list[index].get_table_columns().size(); j++)
			if (attributes[i] == relational_list[index].get_table_columns()[j].get_column_name()){
				columns.push_back(relational_list[index].get_table_columns()[j]);
				attribute_check = true;
			}
			if (attribute_check == false)
				throw runtime_error("Project: no such attribute exists (" + attributes[i] + ")");
		}

		//creating the projection table with attributes data of relational table
		vector<string> t_vec;
		vector<Column> c1;
		for (unsigned int i = 0; i< relational_list[index].get_table_columns().size(); i++){
			vector<string> temp_vec;
			for (unsigned int j = 0; j<columns.size(); j++)
				c1.push_back(relational_list[index].get_table_columns()[i]);
		}
		Table t2(view_name, columns);
		viewing_list.push_back(t2);
		temp_view_table = &t2;
	}
	return *temp_view_table;
} 
  
Table Database::rename(string new_view, string existing_table, vector<string> attributes){ 
    Table& old_table = get_table(existing_table); 
          
    // ERROR - incorrect number of attributes  
    if(old_table.get_table_columns().size() != attributes.size()) 
        throw runtime_error("rename: incorrect number of attributes"); 
          
    vector<Column> c; 
      
    // copy data 
    for(int i = 0; i < old_table.get_table_columns().size(); i++){ 
        c.push_back(old_table.get_table_columns()[i]); 
    } 
  
    // set new key names to reflect new attributes 
	vector<string> attr = old_table.get_keys();

        for(unsigned int i = 0; i < old_table.get_table_columns().size(); ++i){ 
            if(c[i].get_column_name() == old_table.get_table_columns()[i].get_column_name()){   
                c[i].set_column_name(attributes[i]); 
            }
  
        } 
    

    Table t(new_view, c); 
    t.set_keys(attr); 
  
    viewing_list.push_back(t); 
	return t;
} 
  
Table Database::set_union(string view_name, string table1_name, string table2_name){ 
    Table& table1 = get_table(table1_name); 
    Table& table2 = get_table(table2_name); 
  
    //comparing the types of two table types 
    vector<string> table1_type; 
    vector<string> table2_type; 
  
    for(unsigned int i = 0; i < table1.get_table_columns().size(); i++){ 
        table1_type.push_back(table1.get_table_columns()[i].get_column_type()); 
    } 
  
    for(unsigned int i = 0; i < table2.get_table_columns().size(); i++){ 
        table2_type.push_back(table2.get_table_columns()[i].get_column_type()); 
    } 
    // ERROR - non-matching attributes 
    if( table1_type != table2_type) 
        throw runtime_error("set union: non-matching attributes"); 
  
    // set title and copy keys 
    vector<Column> union_columns; 
  
    // copy relation 1 to view table 
    for(unsigned int i = 0; i < table1.get_table_columns().size(); ++i){ 
        union_columns.push_back(table1.get_table_columns()[i]); 
    } 
      
    // copy tuples from relation 2 to view table 
    for(unsigned int i = 0; i < table2.get_table_columns().size(); ++ i){ 
            union_columns.push_back(table2.get_table_columns()[i]); 
    }

	vector<string> key = table1.get_keys();
    // taking away duplicate columns in there 
    for(unsigned int i = 0; i < union_columns.size(); ++i){ 
        for(unsigned int j = i + 1; j < union_columns.size(); ++j){ 
            if(union_columns[i].get_column_name() == union_columns[j].get_column_name()){ 
                        union_columns[i].add_vector_data(union_columns[j].get_column_data()); 
                union_columns.erase(union_columns.begin() + j); 
            } 
        } 
    } 
	vector<int> column_index_keys;
	for(int i = 0; i < union_columns.size(); i++){
		for(int j = 0; j < key.size(); j++){
			if(union_columns[i].get_column_name() == key[j]){
				column_index_keys.push_back(i);
			}
		}
	}

     //removing the duplicate 
 
        for(int j = 0; j < union_columns[0].get_column_data().size(); j++){ 
            for(int k = j+1; k < union_columns[0].get_column_data().size(); k++){ 
				bool is_true = false;
				for(int l = 0; l < column_index_keys.size(); l++){
                if(union_columns[column_index_keys[l]].get_column_data()[j] == union_columns[column_index_keys[l]].get_column_data()[k]){ 
                   is_true = true;
					// union_columns[i].delete_data(k); 
                }
				else{
					is_true = false;
					l = column_index_keys.size();
				}

				}
				if(is_true){
					for(int i = 0; i < union_columns.size(); i++){
						union_columns[i].delete_data(k); 
					}
				}
            } 
        }  
  
    Table t1(view_name, union_columns,table1.get_keys()); 
    viewing_list.push_back(t1); 
	return t1;
      
} 
  
Table Database::set_difference(string view_name, string table1_name, string table2_name){ 
    vector<vector<string> > temp; 
    Table& table1 = get_table(table1_name); 
    Table& table2 = get_table(table2_name); 
    bool equal = false; 
  
    vector<string> table1_type; 
    vector<string> table2_type; 
  
    for(unsigned int i = 0; i < table1.get_table_columns().size(); i++){ 
        table1_type.push_back(table1.get_table_columns()[i].get_column_type()); 
    } 
  
    for(unsigned int i = 0; i < table2.get_table_columns().size(); i++){ 
        table2_type.push_back(table2.get_table_columns()[i].get_column_type()); 
    } 
    // ERROR - non-matching attributes 
    if( table1_type != table2_type) 
        throw runtime_error("set difference: non-matching attributes"); 
  
    // set title and copy keys 
    vector<Column> difference_columns; 

	vector<string> key = table1.get_keys();
  
    // copy relation 1 to view table 
    for(unsigned int i = 0; i < table1.get_table_columns().size(); ++i){ 
        difference_columns.push_back(table1.get_table_columns()[i]); 
    } 
      
    // copy tuples from relation 2 to view table 
   for(unsigned int i = 0; i < table2.get_table_columns().size(); ++ i){ 
            difference_columns.push_back(table2.get_table_columns()[i]); 
    }
    // taking away duplicate columns in there 
    for(unsigned int i = 0; i < difference_columns.size(); ++i){ 
        for(unsigned int j = i + 1; j < difference_columns.size(); ++j){ 
            if(difference_columns[i].get_column_name() == difference_columns[j].get_column_name()){ 
                        difference_columns[i].add_vector_data(difference_columns[j].get_column_data()); 
                difference_columns.erase(difference_columns.begin() + j); 
            } 
        } 
    }

	vector<int> column_index_keys;
	for(int i = 0; i < difference_columns.size(); i++){
		for(int j = 0; j < key.size(); j++){
			if(difference_columns[i].get_column_name() == key[j]){
				column_index_keys.push_back(i);
			}
		}
	}


   //removing the duplicate 
 
        for(int j = 0; j < difference_columns[0].get_column_data().size(); j++){ 
            for(int k = j+1; k < difference_columns[0].get_column_data().size(); k++){ 
				bool is_true = false;
				for(int l = 0; l < column_index_keys.size(); l++){
                if(difference_columns[column_index_keys[l]].get_column_data()[j] == difference_columns[column_index_keys[l]].get_column_data()[k]){ 
                   is_true = true;
					 //difference_columns[j].delete_data(k); 
                }
				else{
					is_true = false;
					l = column_index_keys.size();
				}

				}
				if(is_true){
					for(int i = 0; i < difference_columns.size(); i++){
						difference_columns[i].delete_data(k); 
						difference_columns[i].delete_data(j); 
					}
				}
            } 
        }  
  
  
    Table t1(view_name, difference_columns, table1.get_keys());
	for (int i = 0; i < t1.get_size_of_col_data(); i++)
	{
		for (int j = i + 1; j < t1.get_size_of_col_data(); j++)
		{
			Tuple tup1 = t1.get_tuple(i);
			Tuple tup2 = t1.get_tuple(j);
			if (tup1.get_values() == tup2.get_values())
			{
				t1.erase_row(j);
			}
		}
	}
    viewing_list.push_back(t1); 
	return t1;
  
} 
  
Table Database::cross_product(string view_name, string table1_name, string table2_name){ 
    vector<string> attributes; 
    vector<string> types; 
    vector<Column> cross_p_column; 
    Table& table1 = get_table(table1_name); 
    Table& table2 = get_table(table2_name); 
  
    // merge attributes and attribute types 
    for(int i = 0; i < table1.get_table_columns().size(); i++){ 
        Column c(table1.get_table_columns()[i].get_column_name(), table1.get_table_columns()[i].get_column_type()); 
        cross_p_column.push_back(c); 
    } 
  
    for(int i = 0; i < table2.get_table_columns().size(); i++){ 
		Column c(table2.get_table_columns()[i].get_column_name(), table2.get_table_columns()[i].get_column_type()); 
        cross_p_column.push_back(c); 
    } 
  
    Table t1(view_name, cross_p_column, table1.get_keys()); 
    // perform cross product  
	 for (unsigned int i = 0; i < table1.get_size_of_col_data(); i++) 
		for (unsigned int j = 0; j < table2.get_size_of_col_data(); j++) { 
			 vector<string> tuple_of_1; 
			tuple_of_1 = table1.get_row(i); 
			vector<string> tuple_of_2; 
			tuple_of_2 = table2.get_row(j); 
			vector<string> tuple = tuple_of_1; 
				for (int k = 0; k < tuple_of_2.size(); k++){ 
					tuple.push_back(tuple_of_2[k]); 
				} 

		if (tuple.size() != NULL){ 
			t1.put_row(tuple); 
			} 
		} 
  
  viewing_list.push_back(t1);
  return t1;
} 
  
Table Database::join(string view_name, string table1_name, string table2_name){ 
    Table& table1 = get_table(table1_name); 
    Table& table2 = get_table(table2_name); 
    bool equal = false; 
  
    vector<Column>& table1_columns = table1.get_table_columns(); 
    vector<Column>& table2_columns = table2.get_table_columns(); 
    vector<Column> common_columns; 
    vector<Column> join_columns; 
      
    //getting the common columns between table 1 and table 2 
    for(int i = 0; i < table1_columns.size(); i++){ 
        for(int j = 0; j < table2_columns.size(); j++){ 
            if( table1_columns[i].get_column_name() == table2_columns[j].get_column_name()){ 
                Column c = table1_columns[i];    
                common_columns.push_back(c); 
			} 
        } 
    } 
  
    if(common_columns.size() == 0){ 
       string error = "No common columns for join function."; 
        throw runtime_error(error); 
      } 

	//calling the cross product function
	Table& t1 = cross_product("testing", table1_name, table2_name);

	for(int i = 0; i < t1.get_table_columns().size(); i++){
		Column c = t1.get_table_columns()[i];  
		c.erase_whole_data(); 
		join_columns.push_back(c);
	}
	//creating table with empty columns but contains all the columns
		Table t2(view_name, join_columns, t1.get_keys());
	
	//doing the join function
	for(int i = 0; i < t1.get_table_columns().size()-1; i++){
		for(int j = i+1; j < t1.get_table_columns().size(); j++){
			Column c1 = t1.get_table_columns()[i];
			Column c2 = t1.get_table_columns()[j];
			if(c1.get_column_name() == c2.get_column_name()){
				for(int k = 0; k < t1.get_size_of_col_data();  k++){
					if(c1.get_column_data()[k] ==c2.get_column_data()[k]){
						vector<string> data = t1.get_row(k);
						//putting the data in t2 column
						t2.put_row(data);
					}
				}
				t2.delete_table_column(&c2);
			}
		}
	}

	//deleting the extra tuples that exist
	for(int i = 0; i < t2.get_size_of_col_data(); i++){
		for(int j = i+1; j < t2.get_size_of_col_data(); j++){
			vector<string> data_1 = t2.get_row(i);
			vector<string> data_2 = t2.get_row(j);
			if(data_1 == data_2){
				t2.erase_row(j);
			}

		}
	}
  viewing_list.push_back(t2);
  return t2;
} 
  
/*------------------------------------------------------------------------------------*/
/* INTERNAL UTILITY FUNCTIONS */
/*------------------------------------------------------------------------------------*/ 
  
void Database::print_table(Table& t){ 
    vector<Column>& get_columns = t.get_table_columns(); 
    cout << "Table:  " << t.get_table_name() << endl; 
  
    //printing the attribute names 
    for(unsigned int i = 0; i < get_columns.size(); i++){ 
        cout << left << setw(15); 
        cout << get_columns[i].get_column_name(); 
    } 
    cout << left << setw(15); 
    cout << endl; 
    for(unsigned int i = 0; i < get_columns.size(); i++){ 
          
        cout << get_columns[i].get_column_type(); 
        cout << left << setw(15); 
    } 
    cout << endl; 
    cout << left << setw(15); 
  
    //printing the actual data 
    for(unsigned int j = 0; j < t.get_size_of_col_data(); j++){ 
        for(unsigned int i = 0; i < get_columns.size(); i++){ 
              
            cout << left << setw(15); 
            cout << get_columns[i].get_column_data()[j]; 
        } 
        cout << endl; 
    } 

	cout << endl << endl;
  
  
    } 
  
/*------------------------------------------------------------------------------------*/
/* COMMAND FUNCTIONS */
/*------------------------------------------------------------------------------------*/
vector<vector<string>> Database::show(string table_name){ 
    int index; 
  
	Table* table;

	if ((index = get_relation_index(table_name)) != -1)
	{
		table = &relational_list[index];
	}
	else if ((index = get_view_index(table_name)) != -1)
	{
		table = &viewing_list[index];
	}
    else
        throw runtime_error("show: no such table"); 

	print_table(*table);

	//  push back column names

	vector<vector<string>> vec;
	vector<string> col_names;
	for (int i = 0; i < table->get_table_columns().size(); i++)
	{
		col_names.push_back(table->get_table_columns()[i].get_column_name());
	}
	vec.push_back(col_names);

	for (int i = 0; i < table->get_size_of_col_data(); i++)
	{
		
		vec.push_back(table->get_row(i));
	}

	return vec;
} 
  
void Database::create(string table_name, vector<string> attributes, 
                      vector<string> attribute_types, vector<string> keys){ 
    // check for keys referring to non-existent attributes 
    for(unsigned int i = 0; i < keys.size(); ++i) { 
        unsigned int matching_count = 0; 
        for(unsigned int j = 0; j < attributes.size(); ++j) 
            if(keys[i] == attributes[j]) 
                ++matching_count; 
        if(matching_count == 0) { 
            string error = "create: key ("; 
            error += keys[i]; 
            error += ") does not match any attributes"; 
            throw runtime_error(error); 
        } 
    } 
    // check for duplicate attributes 
    for(unsigned int i = 0; i < attributes.size(); ++i)  
        for(unsigned int j = i + 1; j < attributes.size(); ++j)  
            if(attributes[i] == attributes[j]) { 
                string error = "create: duplicate attribute ("; 
                error += attributes[i]; 
                throw runtime_error(error); 
            } 
   
    // check for existing table 
    if(get_relation_index(table_name) > -1) { 
        string error = "create: table with name ("; 
        error += table_name; 
        error += ") already exists"; 
        throw runtime_error(error); 
    } 
   
    //creating vector of columns 
     vector<Column> attributes_columns; 
    for(unsigned int i = 0; i < attributes.size(); i++){ 
        Column c(attributes[i], attribute_types[i]); 
        attributes_columns.push_back(c); 
    } 
  
  //creating a table with all the columns already added 
    Table tab(table_name, attributes_columns, keys); 
  
  //pushing back the table in the veiwing table 
    relational_list.push_back(tab); 
} 
  
void Database::update(string relation_name, vector<string> attr_names, vector<string> values, Condition& c)
{
  if(attr_names.size() != values.size())
    throw runtime_error("Attributes size and values size don't match");


  bool from_viewing_list;
  bool from_relation_list;

  int list_index = get_relation_index(relation_name);
  if(list_index == -1){
    from_relation_list = false;
    list_index = get_view_index(relation_name);
    if(list_index == -1)
    {
      from_viewing_list = false;
      throw runtime_error("Table to delete from doesn't exist");
    }
    else
      from_viewing_list = true;
  }
  else
  {
    from_relation_list = true;
    from_viewing_list = false;
  }

  Table* table_ptr;

  if(from_relation_list)
  {
	  table_ptr = &relational_list[list_index];
  }
  else if(from_viewing_list)
  {
    table_ptr = &viewing_list[list_index];
  }
  else
    throw runtime_error("Table to delete from doesn't exist");

  for(int i = 0; i < table_ptr->get_size_of_col_data(); i++)
  {
    Tuple t = table_ptr->get_tuple(i);
    if(c.evaluate_tuple(t))
    {
      // tuple satisfies condition, update
      // loop through the attributes passed in
      for(int j = 0; j < attr_names.size(); j++)
      {
        // loop through the table's attributes
        for(int k = 0; k < table_ptr->get_table_columns().size(); k++)
        {
          Column& col = table_ptr->get_table_columns()[k];
          if(attr_names[j] == col.get_column_name())
          {
            // update individual attribute value
            col.get_column_data()[i] = values[j];
            break;
          }
        }
      }
    }
  }
}
  
void Database::insert_tuple(string relation_name, vector<string> tuple){ 
    int table_index; 
  
    vector<int> key_indices; 
  
    if((table_index = get_relation_index(relation_name)) == -1) 
        throw runtime_error("insert_tuple: relation does not exist"); 
  
    Table& table =  relational_list[table_index]; 
  
    if(tuple.size() != table.get_table_columns().size()) 
        throw runtime_error("insert_tuple: incorrect number of attributes"); 
  
    // get keys 
    const vector<string>& keys = table.get_keys(); 
  
    // get indices of attribute keys 
    for(unsigned int i = 0; i < keys.size(); ++i){ 
        key_indices.push_back(get_attribute_index(table,keys[i])); 
    } 
  
    int total_size = table.get_size_of_col_data(); 
    // check for duplicates 
    for(unsigned int i = 0; i < total_size; ++i) { 
        unsigned int dupl_count = 0; 
        for(unsigned int j = 0; j < key_indices.size(); ++j) 
            if(table.get_table_columns()[key_indices[j]].get_column_data()[i] == tuple[key_indices[j]]) 
                ++dupl_count; 
        if(dupl_count == key_indices.size()) 
            throw runtime_error("insert_tuple: duplicate tuple"); 
    } 
  
    //insert the tuple 
    vector<Column>& table_columns = table.get_table_columns(); 
    for(unsigned int i = 0; i < table_columns.size(); i++){ 
        table_columns[i].add_column_data(tuple[i]); 
    } 
} 
  
void Database::insert_view(string relation_name, string view_name){ 
    int view_index = -1; 
    int relation_index = -1; 
    vector<string> keys; 
    vector<int> key_indices; 
  
    if((view_index = get_view_index(view_name)) == -1) 
        throw runtime_error("Insert View: view does not exist");  
    if((relation_index = get_relation_index(relation_name)) == -1) 
        throw runtime_error("Insert View: relation table does not exist"); 
  
    Table& view_table = viewing_list[view_index]; 
    Table& relation_table = relational_list[relation_index]; 
  
    // check for compatibility 
    if(view_table.get_keys() != relation_table.get_keys()) 
        throw runtime_error("insert view: incompatible tables"); 
  
    if(view_table.get_table_columns().size() != relation_table.get_table_columns().size()) 
        throw runtime_error("insert_view: incompatible tables: different attribute types"); 
  
    // get keys 
    for(unsigned int i = 0; i < relation_table.get_keys().size(); ++i) 
        keys.push_back(relation_table.get_keys()[i]); 
  
    // get indices of attribute keys 
    for(unsigned int i = 0; i < keys.size(); ++i) 
        key_indices.push_back(get_attribute_index(relation_table, keys[i])); 
  
    // copy non-duplicate values from view table to relation table 
    for(unsigned int i = 0; i < view_table.get_size_of_col_data(); ++i) { 
        bool duplicate = false; 
        for(unsigned int j = 0; j < relation_table.get_size_of_col_data(); ++j) { 
            unsigned int dupe_count = 0; 
            for(unsigned int k = 0; k < key_indices.size(); ++k) 
                if(view_table.get_row(i)[key_indices[k]] == 
                    relation_table.get_row(j)[key_indices[k]]) 
                    dupe_count++; 
            if(dupe_count == key_indices.size()) 
                duplicate = true; 
        } 
        if(!duplicate){ 
            relation_table.put_row(view_table.get_row(i)); 
        } 
    } 
} 
  
void Database::remove(string relation_name, Condition& c){ 
    int relation_index; 
    if((relation_index = get_relation_index(relation_name)) == -1) 
        throw runtime_error("remove: no such relation"); 
  
    Table& relation_table = relational_list[relation_index]; 
  
	for(int i = 0; i < relation_table.get_size_of_col_data(); i++){
		Tuple tup = relation_table.get_tuple(i);
		bool check = c.evaluate_tuple(tup);
		if(check){
			relation_table.erase_row(i);
		}

	}
}

void Database::delete_from(string relation_name, Condition& c){ 
  bool from_viewing_list;
  bool from_relation_list;

  int list_index = get_relation_index(relation_name);
  if(list_index == -1){
    from_relation_list = false;
    list_index = get_view_index(relation_name);
    if(list_index == -1)
    {
      from_viewing_list = false;
      throw runtime_error("Table to delete from doesn't exist");
    }
    else
      from_viewing_list = true;
  }
  else
  {
    from_relation_list = true;
    from_viewing_list = false;
  }

  Table* table_ptr;

  if(from_relation_list)
  {
	  table_ptr = &relational_list[list_index];
  }
  else if(from_viewing_list)
  {
    table_ptr = &viewing_list[list_index];
  }
  else
    throw runtime_error("Table to delete from doesn't exist");

  for(int i = 0; i < table_ptr->get_size_of_col_data(); i++)
  {
    Tuple t = table_ptr->get_tuple(i);
    if(c.evaluate_tuple(t))
    {
      // tuple satisfies condition, delete
      table_ptr->erase_row(i);
      i--;
    }
  }
} 
  
void Database::remove_table(string table_name){ 
  
    //finding the table index of table with table_name 
    int table_index = get_relation_index(table_name); 
  
    //throwing error if table does not exist 
    if(table_index == -1) 
        throw runtime_error("No such table exists."); 
  
    //erasing the table 
    relational_list.erase(relational_list.begin()+ table_index); 
  
} 

void Database::rename_column(string table_name, string column_old_name, string column_new_name){

  //finding the table index of table with table_name 
    int table_index = get_relation_index(table_name); 
  
    //throwing error if table does not exist 
    if(table_index == -1) 
        throw runtime_error("No such table exists."); 

	//renaming column
	for(int i = 0; i < relational_list[table_index].get_table_columns().size(); i++){
		if(relational_list[table_index].get_table_columns()[i].get_column_name() == column_old_name){
			relational_list[table_index].get_table_columns()[i].set_column_name(column_new_name);
		}
	}
	
}
  
/*------------------------------------------------------------------------------------*/
/* UTILITY FUNCTIONS */
/*------------------------------------------------------------------------------------*/
int Database::get_relation_index(string table_name){ 
    int INDEX = -1; 
  
    for(unsigned int i=0; i <relational_list.size(); i++) 
        if(relational_list[i].get_table_name() == table_name) 
            INDEX = i; 
    return INDEX; 
} 
  
int Database::get_view_index(string table_name){ 
    int INDEX = -1; 
  
    for(unsigned int i=0; i<viewing_list.size(); i++) 
        if(viewing_list[i].get_table_name() == table_name) 
            INDEX = i; 
    return INDEX; 
} 
  
int Database::get_attribute_index(Table& t, string attribute_name){ 
    int COLUMN_INDEX = -1; 
    vector<Column> t_columns = t.get_table_columns(); 
    for(unsigned int i = 0; i < t_columns.size(); i++){ 
        if(t_columns[i].get_column_name() == attribute_name){ 
            COLUMN_INDEX = i; 
            break; 
        } 
    } 
      
    return COLUMN_INDEX; 
} 
  
void Database::update_view_name(string new_name, string old_name){ 
    int VIEW_INDEX = get_view_index(old_name); 
    if(VIEW_INDEX == -1) 
        throw runtime_error("Change View Name: No such table exists"); 
    else
        viewing_list[VIEW_INDEX].set_table_name(new_name); 
} 
  
void Database::update_table_name(string new_name, string old_name){ 
    int VIEW_INDEX = get_relation_index(old_name); 
    if(VIEW_INDEX == -1) 
        throw runtime_error("Change View Name: No such table exists"); 
    else
        relational_list[VIEW_INDEX].set_table_name(new_name); 
} 

void Database::remove_view_table(string table_name){ 
  
    //finding the table index of table with table_name 
    int table_index = get_view_index(table_name); 
  
    //throwing error if table does not exist 
    if(table_index == -1) 
        throw runtime_error("No such table exists."); 
  
    //erasing the table 
    viewing_list.erase(viewing_list.begin()+ table_index); 
  
} 

void Database::remove_relation_table(string table_name){ 
  
    //finding the table index of table with table_name 
    int table_index = get_relation_index(table_name);
  
    //throwing error if table does not exist 
    if(table_index == -1) 
        throw runtime_error("No such table exists."); 
  
    //erasing the table 
    relational_list.erase(relational_list.begin()+ table_index); 
  
} 

  
Table& Database::get_table(string table_name){ 
    int index; 
  
    if((index = get_relation_index(table_name)) != -1) 
        return relational_list[index]; 
	else if((index = get_view_index(table_name)) != -1) 
        return viewing_list[index]; 
    else
        throw runtime_error("get_table: no such table"); 
} 

void Database::exit(){
	relational_list.clear();
	viewing_list.clear();
}