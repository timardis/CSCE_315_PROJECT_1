#include "Parser.h"

Parser::Parser() {
	view_num = 0;
}

void Parser::processInput(string _input)
{
  try
  {
    // Tokenize the input, divide the string input into minimal units
    tokenizer.tokenizeInput(_input);
    
    string token;

    // Check if there is any token
    if(tokenizer.remainingTokens() > 0)
    {
      token = tokenizer.peek();
    }
    else
    {
      // Most likely blank line, return
      return;
    }

    InputType type = getInputType(token);
    switch(type)
    {
    case QUERY:
      processQuery();
      break;
    default:
      processCommand(type);
      break;
    }
  }
  catch(exception& e)
  {
    cout << "Exception: " << e.what() << endl;
  }
}

void Parser::processQuery()
{
  //
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

void Parser::processCommand(InputType type)
{
	switch (type){
	case CREATE:
		createTable();
		break;
	case INSERT:
		insert_into();
		break;
	default:
		break;
	}

}

void Parser::open(string relation_name){
	string file_name = relation_name + ".db";
	ifstream my_file;
	my_file.open(file_name);
	string line;
	if (my_file.is_open()){
		while (getline(my_file, line))
		{
			processInput(line);
		}
	}
	else{
		throw runtime_error("File doesn't exist.\n");
	}
}

void Parser::close(string relation_name){
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
	db.exit();
}

void Parser::show(string table_name){
	db.show(table_name);
}

InputType Parser::getInputType(string _input)
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

ExpressionType Parser::getExpressionType(string _input){
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

void Parser::createTable(){
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
		//call function with relation
	}
	else{
		int brack_count = 0;
		vector<string> data;
		while(brack_count != 2)	{
			string tok = tokenizer.pop();
			if(tok == "(" || tok == ")"){
				brack_count++;
			}
			else if(tok == "\"" || tok == ","){
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
	cout << tok << endl;
	string view_name;
	ExpressionType ex = getExpressionType(tok);
	if(ex == SELECT){
	}
	else if(ex == PROJECT){
		view_name = projection();
	}
	else if(ex == RENAME){
		view_name = rename();
	}
	 
	else{
		view_name = atomic_expression();
					cout << view_name << endl;
		string tok1 = tokenizer.peek();
		ExpressionType ex1 = getExpressionType(tok1);
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
		if(isalpha(tok[0]) ||isdigit(tok[0]) || tok[0] == '_'){
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

/*string Parser::selection(){
	string view_name = get_dummy_view_name();// = relation_name;
	int brack = 0;
	vector<string> condition_data;
	while(brack!= 2){
		string tok = tokenizer.pop();
		if(tok == "(" || tok == ")"){
			brack++;
		}
		else if(tok == "\""){
			continue;
		}
		else{
			condition_data.push_back(tok);
		}
	}
	string table_name = atomic_expression();

}*/

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
