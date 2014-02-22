#include "Parser.h"

Parser::Parser() {
	view_num = 0;
}

void Parser::process_input(string _input)
{
  try
  {
    // Tokenize the input, divide the string input into minimal units
    tokenizer.tokenize_input(_input);
    
    string token;

    // Check if there is any token
    if(tokenizer.remaining_tokens() > 0)
    {
      token = tokenizer.peek();
    }
    else
    {
      // Most likely blank line, return
      return;
    }

    InputType type = get_input_type(token);
    switch(type)
    {
    case QUERY:
      process_query();
      break;
    default:
      process_command(type);
      break;
    }
  }
  catch(exception& e)
  {
    cout << "Exception: " << e.what() << endl;
  }
}

void Parser::process_query()
{
  string expected_name = tokenizer.pop();

  string t1 = tokenizer.pop();

  if (t1 != "<-")
  {
	    throw runtime_error("Invalid Input");
  }
  string dummy_name = expression();

  db.update_view_name(expected_name, dummy_name);
  db.show(expected_name);

}

void Parser::process_command(InputType type)
{
	switch (type){
	case CREATE:
		create_table();
		break;
	case INSERT:
		insert_into();
		break;
	case OPEN:
		open();
		break;
	case CLOSE:
		close();
		break;
	case WRITE:
		write();
		break;
	case SHOW:
		show();
		break;
	case EXIT:
		exit();
		break;
	case DELETE:
		delete_from();
		break;
	default:
		break;
	}

}

void Parser::open(){
	string tok = tokenizer.pop();
	string relation_name = tokenizer.pop();
	string file_name = relation_name + ".db";
	ifstream my_file;
	my_file.open(file_name);
	string line;
	if (my_file.is_open()){
		while (getline(my_file, line))
		{
			process_input(line);
		}
	}
	else{
		throw runtime_error("File doesn't exist.\n");
	}
}

void Parser::close(){
	string relation_name = tokenizer.pop();
	string file_name = relation_name + ".db";
	ifstream my_file(file_name);
	if (my_file.is_open()){
		my_file.close();
	}
	else{
		throw runtime_error("The file was never open in the first place.");
	}
}

void Parser::exit(){
	string tok = tokenizer.pop();
	db.exit();
}

void Parser::write(){
	string tok = tokenizer.pop();
	string table_name = tokenizer.pop();
	Table t = db.get_table(table_name);
	ofstream output_file;
	output_file.open(table_name + ".db");
	output_file << "CREATE TABLE " << table_name << " (";

	for(int i = 0; i < t.get_table_columns().size(); i++){
		if(i != t.get_table_columns().size()-1){
			output_file << t.get_table_columns()[i].get_column_name() << " "
				<< t.get_table_columns()[i].get_column_type() << ", ";
		}
		else{
			output_file << t.get_table_columns()[i].get_column_name() << " "
				<< t.get_table_columns()[i].get_column_type() << ") ";
		}
	}
	output_file << "PRIMARY KEY (";
	for(int i = 0; i < t.get_keys().size(); i++){
		if(i != t.get_keys().size()-1){
			output_file <<  t.get_keys()[i] << ", ";
		}
		else{
			output_file <<  t.get_keys()[i] << ");" << endl;
		}
	}

	for(int i = 0; i < t.get_size_of_col_data(); i++){
		output_file << "INSERT INTO " << table_name << " VALUES FROM (";
		vector<string> tuple_row = t.get_row(i);
		for(int j = 0; j < tuple_row.size(); j++){
			if(j != tuple_row.size()-1){
				if(t.get_table_columns()[j].get_column_type() == "INTEGER"){
					output_file << tuple_row[j] << ", ";
				}
				else{
					output_file << "\"" <<  tuple_row[j] << "\", ";
				}
			}
			else{
				if(t.get_table_columns()[j].get_column_type() == "INTEGER"){
					output_file << tuple_row[j] << ");" << endl;
				}
				else{
					output_file << "\"" <<  tuple_row[j] << "\";" << endl;
				}
			}
		}
	}
	output_file.close();
}

void Parser::delete_from(){
	string tok1 = tokenizer.pop();
	string tok2 = tokenizer.pop();
	string relation_name = tokenizer.pop();
	string tok3 = tokenizer.pop();
	if(tok3 != "WHERE");
	throw runtime_error("Wrong function call for delete");
	Condition con(tokenizer);
	//db.remove(relation_name, con);
}

void Parser::show(){
	string tok = tokenizer.pop();
	if(tok != "SHOW"){
		throw runtime_error("wrong function call");
	}
	string table_name = atomic_expression();
	db.show(table_name);
  string relation_name = tokenizer.pop();

  // query ::= relation-name <- expr;
  string t1 = tokenizer.pop();
  string t2 = tokenizer.pop();

  if (t1 == "<")
  {

  }
  else
  {
    throw runtime_error("Invalid Input");
  }

  //Table t = expression(input);
}


Table Parser::expression(string _input)
{
  // Dummy code to compile
  Table* t = NULL;
  return *t;
}

InputType Parser::get_input_type(string _input)
{
  smatch m;
  if (regex_search(_input, m, regex("^[[:blank:]]*([a-zA-Z1-9]+)[[:blank:]]*")))
  {
    string op = m[1].str();

    if(op == string("OPEN"))
    {
      return OPEN;
    }
    else if(op == string("CLOSE"))
    {
      return CLOSE;
    }
    else if(op == string("WRITE"))
    {
      return WRITE;
    }
    else if(op == string("EXIT"))
    {
      return EXIT;
    }
    else if(op == string("SHOW"))
    {
      return SHOW;
    }
    else if(op == string("CREATE"))
    {
      return CREATE;
    }
    else if(op == string("UPDATE"))
    {
      return UPDATE;
    }
    else if(op == string("INSERT"))
    {
      return INSERT;
    }
    else if(op == string("DELETE"))
    {
      return DELETE;
    }
    else
    {
      return QUERY;
    }
  }
  else
  {
    throw runtime_error("Invalid Input");
  }
}

ExpressionType Parser::get_expression_type(string _input){
	if(_input == "select"){
		return SELECT;
	}
	else if(_input == "project"){
		return PROJECT;
	}
	else if(_input == "rename"){
		return RENAME;
	}
	else if(_input == "+"){
		return UNION;
	}
	else if(_input == "-"){
		return DIFFERENCE;
	}
	else if(_input == "*"){
		return PRODUCT;
	}
	else if(_input == "JOIN"){
		return NATURAL_JOIN;
	}
	else{
		return ATOMIC_EXPR;
	}

}

void Parser::create_table(){
	string t1 = tokenizer.pop();
	string t2 = tokenizer.pop();
	if (t1 == "CREATE" && t2 == "TABLE"){
		string table_name = tokenizer.pop();
		pair<vector<string>, vector<string>> typed_attributes_lists = get_typed_attribute_list();
		vector<string> attribute_names = typed_attributes_lists.first;
		
		vector<string> attribute_types = typed_attributes_lists.second;
		vector<string> keys = get_keys();
		db.create(table_name, attribute_names, attribute_types, keys);
	}
	else{
		throw runtime_error("invalid create table function called1\n");
	}
}

void Parser::insert_into(){
	string tok0 = tokenizer.pop();
	string tok1 = tokenizer.pop();
	if(tok1 != "INTO"){
		throw runtime_error("wrong function call for INSERT INTO\n");
	}
	string table_name = tokenizer.pop();
	Table& t = db.get_table(table_name);
	string tok2 =  tokenizer.pop();
	string tok3 =  tokenizer.pop();
	if(tok2!= "VALUES" || tok3 != "FROM"){
		throw runtime_error("wrong function call for INSERT INTO\n");
	}
	string tok4 = tokenizer.peek();
	if(tok4 == "RELATION"){
		string view_name = expression();
		Table t = db.get_table(view_name);
		for(int i = 0; i < t.get_size_of_col_data(); i++){
			db.insert_tuple(table_name, t.get_row(i));
		}
	}
	else{
		int brack_count = 0;
		vector<string> data;
		string full_data = "";
		int quotes_count = 0;
		while(brack_count != 2)	{
			string tok = tokenizer.pop();
			if(tok == "(" || tok == ")"){
				brack_count++;
			}
			else if(tok == "\""){
				string new_tok = tokenizer.peek();
				full_data = tokenizer.pop();
				while(new_tok != "\""){
					if(full_data != new_tok)
						full_data += " " +  new_tok;
					new_tok = tokenizer.pop();
				}
				data.push_back(full_data);
			}
			else if( tok == ","){
				continue;
			}
			else{
				data.push_back(tok);
			}
		}
		t.put_row(data);
	}
}

pair<vector<string>, vector<string>> Parser::get_typed_attribute_list(){
	pair<vector<string>, vector<string>> typed_attribute_lists;
	string t1 = tokenizer.pop();
	
	bool is_left_brac = false;
	if (t1 == "("){
		while(!is_left_brac){
			string t2 = tokenizer.pop();
			if (t2 == ")"){
				is_left_brac = true;
			}
			
			else{
				 if (t2 == ","){
					t2 = tokenizer.pop();
				}
				typed_attribute_lists.first.push_back(t2);
				string t3 = get_attribute_type();
	
			
					typed_attribute_lists.second.push_back(t3);
				
			}
		}
		return typed_attribute_lists;
	}
	
	else{
		throw runtime_error("invalid create table function called2\n");
	}

}

string Parser::get_attribute_type(){
	string tok1 = tokenizer.pop();
	string tok2 = tokenizer.peek();
	if (tok2 == "("){
		tok2 = tokenizer.pop();
		tok2 += tokenizer.pop();
		string tok3 = tokenizer.pop();
		if (tok3 == ")")
			tok2 += tok3;
		string tok4 = tok1 + tok2;
		return tok4;
	}
	else if(tok2 == ","){
		tok2 = tokenizer.pop();
		return tok1;
	}
	else if (tok2 == ")"){
		return tok1;
	}
	else{
		throw runtime_error("invalid create table function called3\n");
	}

}

vector<string> Parser::get_keys(){
	string t1 = tokenizer.pop();
	string t2 = tokenizer.pop();
	vector<string> key;

	//to keep track of how many ( or ) exists
	int brack_count = 0;

	if (t1 == "PRIMARY" && t2 == "KEY"){
		while (brack_count != 2){
			string tok = tokenizer.pop();
			if (tok == "(" || tok == ")"){
				brack_count++;
			}
			else if (tok == ","){
				continue;
			}
			else if (tok == ";"){
				throw runtime_error("invalid create table function called4\n");
			}
			else{
				key.push_back(tok);

			}
		}
	
	}
	else{
		throw runtime_error("invalid create table function called5\n");
	}

	return key;

}

string Parser::expression(){
	string tok = tokenizer.pop();
	string view_name;
	ExpressionType ex = get_expression_type(tok);
	if(ex == SELECT){
		view_name = selection();
	}
	else if(ex == PROJECT){
		view_name = projection();
	}
	else if(ex == RENAME){
		view_name = rename();
	}
	 
	else{
		view_name = atomic_expression();
		string tok1 = tokenizer.peek();
		
		ExpressionType ex1 = get_expression_type(tok1);
		if(ex1 == UNION){
			tokenizer.pop();
			view_name = set_union_parser(view_name);
		}
		else if(ex1 == DIFFERENCE){
			tokenizer.pop();
			view_name = set_difference_parser(view_name);
		}
		else if(ex1 == PRODUCT){
			tokenizer.pop();
			view_name = cross_product_parser(view_name);
		}
		else if(ex1 == NATURAL_JOIN){
			tokenizer.pop();
			view_name = set_natural_join(view_name);
		}
	}
	return view_name;
}

string Parser::atomic_expression(){
	string view_name;
	string tok = tokenizer.peek();
	if(tok == "("){
		string tok2 = tokenizer.pop();
		view_name = expression();
		string tok1 = tokenizer.pop();
		if(tok1 != ")"){
			throw runtime_error("atomic expression: unexpected symbol");
		}
	}
	else{
		if(tok == "JOIN"){
			view_name = tokenizer.get_previous_data();
		}
		else if(isalpha(tok[0]) ||isdigit(tok[0]) || tok[0] == '_' ){
			string tok2 = tokenizer.pop();
			view_name = tok2;
		}
		else
		{
			view_name = tokenizer.get_previous_data();
		}
	}
	return view_name;
}

string Parser::selection(){
	string view_name = get_dummy_view_name();// = relation_name;
	Condition c(tokenizer);
	string table_name = atomic_expression();
	db.select(view_name, table_name, c);
	return view_name;

}

string Parser::projection(){
	string view_name = get_dummy_view_name();
	vector<string> attributes;
	string tok = tokenizer.pop();
	if(tok != "("){
		throw runtime_error("projection: expected '('");
	}
	attributes = get_attribute_list(); 
	string relation_name = atomic_expression();
	db.project(view_name, relation_name, attributes);
	return view_name;
}

string Parser::rename(){
	string view_name = get_dummy_view_name();
	vector<string> attributes;
	string tok = tokenizer.pop();
	if(tok != "("){
		throw runtime_error("projection: expected '('");
	}
	attributes = get_attribute_list();
	string relation_name = atomic_expression();
	db.rename(view_name, relation_name, attributes);
	return view_name;
}

string Parser::set_union_parser(string left_atom_exp){
	string view_name = get_dummy_view_name();
	string right_atom_exp = atomic_expression();
	db.set_union(view_name, left_atom_exp, right_atom_exp);
	return view_name;
}

string Parser::set_difference_parser(string left_atom_expr){
	string view_name = get_dummy_view_name();
	string right_atom_exp = atomic_expression();
	db.set_difference(view_name, left_atom_expr, right_atom_exp);
	return view_name;
}

string Parser::cross_product_parser(string left_atom_expr){
	string view_name = get_dummy_view_name();
	string right_atom_exp = atomic_expression();
	db.cross_product(view_name, left_atom_expr, right_atom_exp);
	return view_name;
}

string Parser::set_natural_join(string left_atom_expr){
	string view_name = get_dummy_view_name();
	string right_atom_exp = atomic_expression();
	db.join(view_name, left_atom_expr, right_atom_exp);
	return view_name;
}

  vector<string> Parser::get_attribute_list(){
	  vector<string> attr_list;
	 
	  bool is_brack = false;
	  while(!is_brack){
		   string tok1 = tokenizer.pop();
		if(tok1 == ")"){
		 is_brack = true;
		}
		else if(tok1 == ","){
		  continue;
		 }
		else{
		  attr_list.push_back(tok1);
			}
	  }
	  if(attr_list.size() == 0){
		  throw runtime_error("project: no attributes were given. ");
	  }
	  return attr_list;
  }

string Parser::get_dummy_view_name(){
	string view_name = to_string(view_num);
	++view_num;
	return view_name;
}
