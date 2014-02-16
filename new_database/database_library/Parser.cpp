#include "Parser.h"

Parser::Parser() {}

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

Table Parser::expression(string _input)
{
  // Dummy code to compile
  Table* t = NULL;
  return *t;
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
		db.show(table_name);
	}
	else{
		throw runtime_error("invalid create table function called1\n");
	}
}

void Parser::insert_into(){
	string tok0 = tokenizer.pop();
	string tok1 = tokenizer.pop();
	cout << tok1 << endl;
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
		cout << data.size();
		t.put_row(data);
		db.show(table_name);
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