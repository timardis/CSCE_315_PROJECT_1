#include "parser.h"
#include <iostream>
#include <fstream>

using namespace std;

Token_stream ts;

//function returns a letter (checks if uppercase or lowercase)
char parser::alpha() 
{
	Token t = ts.get();

	switch (t.kind) 
	{
	case '9': case '7':
		return t.letter;
	default:
		return '\0';
	}
}

//returns a string identifier
string parser::identifier() {

	int quote_counter = 0; //quote counter used to determine when inside and outside of quotes
	string id = "";
	Token t = ts.get();
	int keep_going = 1;

	if (t.kind != '"') 
	{ //only put back character if it is an alpha
		ts.putback(t);
	}	

	while (keep_going) 
	{
		switch (t.kind) 
		{
		case '9':
			id += alpha(); //add each letter in stream to identifier
			t = ts.get();
			ts.putback(t);
			break;

		case '7':
			ts.putback(t);

			if (quote_counter < 2 && quote_counter >= 1) 
			{
				id += alpha();
				t = ts.get();
				ts.putback(t);				
			}

			else 
			{
				keep_going = 0;
				return id;
			}
			
			break;

		case '"':
			quote_counter++;
			if (quote_counter == 2) { //second quote encountered, end of identifier
				ts.get();
				return id;
			}
			t = ts.get();
			if (t.kind != '"') {
				ts.putback(t);
			}			
			break;

		case '8': //keep integers in identifier
			id += to_string(t.value);
			ts.get();
			t = ts.get();
			ts.putback(t);
			break;

		case '_': //keep underscores in identifier
			id += t.kind;
			ts.get();
			t = ts.get();
			ts.putback(t);
			break;

		default: //done, return the string
			return id;
		}
	}
}



//comparison object of two operands and an operation
comparison_obj parser::comparison() 
{
	comparison_obj comp;
	Token t = ts.get();
	string _oper1, _oper2 = "";
	string _op = "";
	int keep_going = 1;

	while (keep_going) 
	{
		switch (t.kind) 
		{
		case '8':
			_oper2 = to_string(t.value);
			keep_going = 0;
			break;
		
		case '9':
			ts.putback(t);
			_oper1 = identifier();

			t = ts.get();
			break;

		case '"':
			ts.putback(t);
			_oper2 = identifier();

			t = ts.get();
			break;

		case '<':
			_op += t.kind;
			t = ts.get();
			
			if (t.kind == '=') 
			{
				_op += t.kind;
				t = ts.get();
			}

			else if (t.kind == '9') 
			{
				_oper2 = identifier();
				keep_going = 0;
			}

			break;

		case '>':
			_op += t.kind;
			t = ts.get();
			
			if (t.kind == '=') 
			{
				_op += t.kind;
				t = ts.get();
			}

			else if (t.kind == '9') 
			{
				_oper2 = identifier();
				keep_going = 0;
			}

			break;

		case '=':
			_op += t.kind;
			t = ts.get();
			
			if (t.kind == '=') 
			{
				_op += t.kind;
				t = ts.get();
			}

			else if (t.kind == '9') 
			{
				_oper2 = identifier();
				keep_going = 0;
			}

			break;

		case '!':
			_op += t.kind;
			t = ts.get();
			
			if (t.kind == '=') 
			{
				_op += t.kind;
				t = ts.get();
			}
			else if (t.kind == '9' || t.kind == '"') 
			{
				_oper2 = identifier();
				keep_going = 0;
			}

			break;

		case ';': //end of line
			ts.putback(t);
			keep_going = 0;

		default:
			ts.putback(t);
			keep_going = 0;
		}
	}

	comp.oper1 = _oper1;
	comp.op = _op;
	comp.oper2 = _oper2;
	return comp;
}

//comparison && comparison
conjunction_obj parser::conjunction() 
{
	conjunction_obj conjun;
	Token t = ts.get();
	int keep_going = 1;
	while (keep_going) 
	{
		switch (t.kind) 
		{
		case '9':
			ts.putback(t);
			conjun.comparisons.push_back(comparison());
			t = ts.get();
			break;

		case '&':
			ts.get();
			conjun.comparisons.push_back(comparison());
			t = ts.get();
			break;	

		case ';':
			ts.putback(t);
			return conjun;

		default:
			ts.putback(t);
			keep_going = 0;
			return conjun;
		}
	}
}
//conjunction || conjunction
condition_obj parser::condition() 
{
	condition_obj condit;
	Token t = ts.get();
	int keep_going = 1;

	while (keep_going) 
	{
		switch (t.kind) 
		{
		case '9':
			ts.putback(t);
			condit.conjunctions.push_back(conjunction());
			t = ts.get();
			break;

		case '|':
			ts.get();
			condit.conjunctions.push_back(conjunction());
			t = ts.get();
			break;

		case ';':
			ts.putback(t);
			return condit;

		case ')':
			ts.putback(t);
			return condit;

		default:
			ts.putback(t);
			keep_going = 0;
		}
	}
}


//returns a keyword (uppercase strings)
string parser::keyword() 
{

	string id = "";
	Token t = ts.get();
	ts.putback(t);

	while (1) {
		switch (t.kind) 
		{
		case '7':
			id += alpha();
			t = ts.get();
			ts.putback(t);
			break;

		default:
			return id;
		}
	}
}
//a tables name, or views
string parser::relation_name() 
{
	return identifier();
}

//a header to a column in a table
string parser::attribute_name() {
	return identifier();
}

//relation name or an expression
table parser::atomic_expr() 
{
	Token t = ts.get();
	int keep_going = 1;

	while (keep_going) 
	{
		switch (t.kind) 
		{
		case '9':
			ts.putback(t);
			return db_ptr.get_table(relation_name());
			t = ts.get();
			break;

		case '(':
			return expr();
			t = ts.get();
			break;

		default:
			keep_going = 0;
			break;
		}
	}
}

//returns a table based on some query
table parser::expr() 
{
	Token t = ts.get();
	string result;
	int keep_going = 1;

	while (keep_going) 
	{
		switch (t.kind) 
		{
		case '9':
			ts.putback(t);
			result = identifier();
			t = ts.get();
			keep_going = 0;
			break;

		default:
			keep_going = 0;
		}
	}
	if (result == "select") 
	{
		ts.putback(t);
		return selection_qry();
	}
	else if (result == "project") 
	{
		ts.putback(t);
		return projection_qry();
	}
	else if (result == "rename") 
	{
		ts.putback(t);
		return renaming_qry();
	}
	else 
	{
		for (int i = 0; i < result.size() + 2; i++)  //if not select/project/rename, put back characters on cin so they can be read
		{	
			cin.unget();
		}

		return tables_qry();
	}
}

//varchar or integer
int parser::type() 
{
	Token t = ts.get();
	ts.putback(t);
	string temp;

	while (1) 
	{
		switch (t.kind) 
		{
		case '7':
			temp = keyword();
			if (temp == "VARCHAR") 
			{
				return 1; //varchar type
			}
			else if (temp == "INTEGER")
			{
				return 2; //integer type
			}
		}
	}
}

pair<int, int> parser::attr_type() 
{
	pair<int, int> pair;
	int which_type = type();
	Token t = ts.get();

	switch (which_type) 
	{
	case 1:
		pair.first = 1;
		t = ts.get();

		if (t.kind == '8') 
		{
			pair.second = t.value;
		}
		ts.get();
		break;

	case 2:
		pair.first = 2;
		pair.second = 0;
		ts.putback(t);

		break;
	}
	return pair;
}

//attribute name types, intgeters and varchars
typed_attribute parser::typed_attribute_list() 
{
	typed_attribute ta_list;

	string attr;
	pair<int, int> type;
	Token t = ts.get();
	ts.putback(t);

	while (1) 
	{
		switch (t.kind) 
		{
		case '9':
			attr = attribute_name();
			type = attr_type();
			t = ts.get();
			break;

		case ',':
			ta_list.list.push_back(attr);
			ta_list.types.push_back(type);
			t = ts.get();
			ts.putback(t);
			break;

		case ')':
			ta_list.list.push_back(attr);
			ta_list.types.push_back(type);
			return ta_list;
		}
	}
}

//a list of pairings of attributes
vector<string> parser::attribute_list() 
{
	vector<string> list;
	string attr;
	Token t = ts.get();

	if (t.kind != '"') 
	{
		ts.putback(t);
	}	

	while (1) 
	{
		switch (t.kind) 
		{
		case '"':
			t = ts.get();
			break;

		case '9':
			ts.putback(t);
			attr = attribute_name();
			t = ts.get();
			break;

		case ',':
			list.push_back(attr);
			t = ts.get();
			ts.putback(t);
			break;

		case ')':
			ts.putback(t);
			list.push_back(attr);
			return list;
		}
	}
}

//list of literals
vector<string> parser::literal_list() 
{
	vector<string> list;
	string id;
	Token t = ts.get();
	while (1) 
	{
		switch (t.kind) 
		{
		case '"':
			ts.putback(t);
			id = identifier();
			list.push_back(id);
			t = ts.get();
			break;

		case ',':
			t = ts.get();
			break;

		case '8':
			list.push_back(to_string(t.value));
			t = ts.get();
			break;

		case ')':
			return list;
		}
	}
}
//insert an entity into a table
void parser::insert_cmd()  
{
	Token t = ts.get();
	string name;
	vector<string> literals;
	int keep_going = 1;

	while (keep_going) 
	{
		switch (t.kind) 
		{
		case '9':
			ts.putback(t);
			name = relation_name();
			t = ts.get();
			break;

		case '7':
			ts.putback(t);
			if (keyword() == "VALUESFROM") 
			{
				t = ts.get();
				literals = literal_list();
			}
			keep_going = 0;
			break;
		}
	}

	db_ptr.get_table(name).insert(literals);
}
//update entities that meet some condition with set values
void parser::update_cmd() 
{
	Token t = ts.get();
	condition_obj condits;
	string name;
	string attr_name;
	vector<pair<string, string>> sets; //pair<string, string> is <attribute, new-value>
	int keep_going = 1;

	while (keep_going) 
	{
		switch (t.kind) 
		{
		case '9':
			ts.putback(t);
			name = relation_name();
			t = ts.get();
			break;

		case '7':
			ts.putback(t);
			string temp_keyword = keyword();
			if (temp_keyword == "SET") 
			{
				int keep_going2 = 1;
				pair<string, string> temp;
				t = ts.get();
				while (keep_going2) 
				{									
					switch (t.kind) 
					{
					case '9':
						ts.putback(t);
						temp.first = attribute_name();
						t = ts.get();
						break;

					case '=':
						temp.second = identifier();
						t = ts.get();
						break;

					case ',':
						sets.push_back(temp);
						t = ts.get();
						break;

					case '7':
						sets.push_back(temp);
						ts.putback(t);
						keep_going2 = 0;
						break;
					}
				}
			}

			else if (temp_keyword == "WHERE") 
			{
				condits = condition();
				keep_going = 0;
			}
			break;
		}
	}

	db_ptr.get_table(name).update(sets, condits);
}

//creates a table and adds it to database
table parser::create_cmd() 
{
	Token t = ts.get();
	string name;
	typed_attribute ta_list;
	vector<string> primary_key_list;
	int keep_going = 1;

	while (keep_going) 
	{
		switch (t.kind) 
		{
		case '9':
			ts.putback(t);
			name = relation_name();
			t = ts.get();
			break;

		case '7':
			ts.putback(t);
			if (keyword() == "PRIMARYKEY") 
			{
				t = ts.get();
				primary_key_list = attribute_list();
			}
			keep_going = 0;
			break;

		case '(':
			ta_list = typed_attribute_list();
			t = ts.get();
			break;
		}
	}
	table temp(name, ta_list.list, primary_key_list);
	cout << "table created succesfully" << endl;
	return temp;
}

//calls display function on a table name
string parser::show_cmd() 
{
	Token t = ts.get();
	string name;
	int keep_going = 1;

	while (keep_going) 
	{
		switch (t.kind) 
		{
		case '9':
			ts.putback(t); 
			name = relation_name();
			t = ts.get();
			keep_going = 0;
			update_data_vec(name);
			return name;
			break;

		case '7':
			ts.putback(t);
			if (keyword() == "SHOW") 
			{
				t = ts.get();
			}
			break;

		default:{
				update_data_vec(name);
				return name;
		}
		}
	}
}


//prints and saves a table into an output file, and closes table from database
string parser::close_cmd() 
{

	table tble;
	ofstream myfile;

	Token t = ts.get();
	string name;
	ts.putback(t);//does not continue to have name

	name = relation_name();
	myfile.open(name + ".db");

	myfile << name << endl;

	tble = db_ptr.get_table(name);

	for (int i = 0; i < tble.attribute_names.size(); i++)
	{
		myfile << tble.attribute_names[i] << ' ';
	}

	myfile << endl;

	for (int i = 0; i < tble.primary_key.size(); i++)
	{
		myfile << tble.primary_key[i] << ' ';
	}
	myfile << endl;

	for (int i = 0; i < tble.entity_table.size(); i++)
	{
		for (int j = 0; j <tble.attribute_names.size(); j++)
		{
			myfile << tble.entity_table[i].attributes[tble.attribute_names[j]] << ' ';
		}
		myfile << endl;
	}


	myfile.close();
	return name;
}

//selection query for databse to select expressions
table parser::selection_qry() 
{
	int num_of_parentheses = 0;
	Token t = ts.get();
	condition_obj condits;
	table to_return;
	string view_name;
	int keep_going = 1;

	while (keep_going) 
	{
		switch (t.kind) 
		{
		case '(':
			num_of_parentheses++;
			if (num_of_parentheses < 2) 
			{
				condits = condition();
			}

			else 
			{			
				to_return = expr();
			}

			t = ts.get();
			break;

		case ')':
			to_return = atomic_expr();
			t = ts.get();
			if (t.kind == ';') 
			{
				break;
			}
			else 
			{
				t = ts.get();
				ts.putback(t);
			}			
			break;

		case ';':
			return db_ptr.set_selection(view_name, to_return, condits);
			keep_going = 0;
		}
	}
}

//rename query that renames entities based on some condition
table parser::renaming_qry() {

	int num_of_parentheses = 0;
	Token t = ts.get();
	vector<string> attr_list;
	table to_return;
	string name;
	int keep_going = 1;

	while (keep_going) 
	{
		switch (t.kind) 
		{
		case '(':
			num_of_parentheses++;
			if (num_of_parentheses < 2) 
			{
				attr_list = attribute_list();				
			}
			else 
			{
				to_return = expr();			
			}
			t = ts.get();
			break;

		case ')':
			to_return = atomic_expr();
			t = ts.get();
			if (t.kind = ';') 
			{
				break;					
			}
			else 
			{
				t = ts.get();					
			}
			break;

		case ';':
			return db_ptr.set_renaming(name, to_return, attr_list);
			keep_going = 0;					
		}
	}
}
table parser::projection_qry() 
{
	int num_of_parentheses = 0;
	Token t = ts.get();
	vector<string> attr_list;
	table to_return;
	string view_name;
	int keep_going = 1;

	while (keep_going) 
	{
		switch (t.kind) 
		{
		case '(':
			num_of_parentheses++;

			if (num_of_parentheses < 2) 
			{
				attr_list = attribute_list();
			}
			t = ts.get();
			break;

		case ')':
			to_return = atomic_expr();
			t = ts.get();

			if (t.kind == ';') 
			{
				break;
			}

			else 
			{
				t = ts.get();
			}
			break;

		case ';':
			return db_ptr.set_projection(view_name, to_return, attr_list);
			keep_going = 0;
		}
	}
}

//query which accepts two table names (union, difference, cross product, natural join)
table parser::tables_qry() 
{
	Token t = ts.get();
	table left, right;
	int assign_right = 0;
	string view_name;
	char op;
	int keep_going = 1;

	while (keep_going) 
	{
		switch (t.kind) 
		{
		case '9':
			ts.putback(t);

			if (assign_right == 0) 
			{
				left = atomic_expr();
				assign_right += 1;
			}
			else if (assign_right == 1) 
			{
				right = atomic_expr();
			}
			t = ts.get();
			break;

		case '+': case '-': case '*':
			op = t.kind;
			right = atomic_expr();
			t = ts.get();
			break;

		case ';': case ')':
			switch (op) 
			{
			case '+':
				return db_ptr.set_union(view_name, left, right);
				break;

			case '-':
				return db_ptr.set_difference(view_name, left, right);
				break;

			case '*':
				return db_ptr.set_cross_product(view_name, left, right);
				break;
			}			
		}
	}
}

void parser::delete_cmd() 
{
	Token t = ts.get();
	string name;
	condition_obj condits;

	int keep_going = 1;

	while (keep_going) 
	{
		switch (t.kind) 
		{
		case '9':
			ts.putback(t);
			name = identifier();
			t = ts.get();
			break;

		case '7':
			ts.putback(t);
			string temp_keyword = keyword();
			if (temp_keyword == "WHERE") {
				condits = condition();
				keep_going = 0;
			}
			break;
		}
	}
	db_ptr.get_table(name).delete_from(condits);

}

void parser::exit_cmd() 
{

	cout << "You are logging out. Have a Good Day." << endl;

	exit(0);


}

vector<string> parser::split_on_spaces(string str) 
{
	istringstream iss(str);
	string s;
	vector<string> result;

	while (getline(iss, s, ' '))
	{
		result.push_back(s.c_str());
	}

	return result;
}

void parser::open_cmd() 
{

	table tble;

	Token t = ts.get();						//used to get the name of the file
	string name;							//name+.db is where you will open from
	ts.putback(t);

	name = relation_name();				//have name to use in open statmeent

	string line, tmp_contents;
	ifstream myfile(name + ".db", ifstream::in);

	if (myfile.is_open())
	{
		getline(myfile, line);
		string tbl_name = line;
		getline(myfile, line);
		vector<string> attr_list = split_on_spaces(line);
		getline(myfile, line);
		vector <string> prmy_key = split_on_spaces(line);

		db_ptr.create_table(tbl_name, attr_list, prmy_key);
		while (getline(myfile, line))
		{
			cout << line << endl;
			db_ptr.get_table(name).insert(split_on_spaces(line));
		}
		myfile.close();
	}
	else cout << "Unable to open file" << endl;

}
void parser::write_cmd() 
{

	table tble;
	ofstream myfile;

	Token t = ts.get();
	string name;
	ts.putback(t);//does not continue to have name

	name = relation_name();
	myfile.open(name + ".db");

	myfile << name << endl;

	if (db_ptr.find_table(name) > -1)
	{
		tble = db_ptr.get_table(name);
	}

	for (int i = 0; i < tble.attribute_names.size(); i++)
	{
		myfile << tble.attribute_names[i] << ' ';
	}

	myfile << endl;
	for (int i = 0; i < tble.primary_key.size(); i++)
	{
		myfile << tble.primary_key[i] << ' ';
	}
	myfile << endl;

	for (int i = 0; i < tble.entity_table.size(); i++)
	{
		for (int j = 0; j <tble.attribute_names.size(); j++)
		{
			myfile << tble.entity_table[i].attributes[tble.attribute_names[j]] << ' ';
		}
		myfile << endl;
	}
	myfile.close();
}
void parser::evaluate_statement()
{
	Token t = ts.get();
	ts.putback(t);
	int keep_going = 1;
	table query_view;
	string key_word;
	string new_view;
	string operation_or_name;

	while (keep_going) 
	{
		switch (t.kind) 
		{
		case '7':
			ts.putback(t);
			key_word = keyword();
			if (key_word == "SHOW") 
			{
				db_ptr.get_table(show_cmd()).display_table();
				data_vec = db_ptr.get_tab_data(show_cmd());
				t = ts.get();
			}
			else if (key_word == "DELETEFROM") 
			{
				delete_cmd();
				t = ts.get();
			}
			else if (key_word == "CREATETABLE") 
			{
				db_ptr.add_table(create_cmd());
				t = ts.get();
			}
			else if (key_word == "EXIT") 
			{
				exit_cmd();
			}
			else if (key_word == "CLOSE") 
			{
				db_ptr.delete_table(db_ptr.get_table(close_cmd())); 
				t = ts.get();
			}
			else if (key_word == "UPDATE") 
			{
				update_cmd();			
				t = ts.get();				
			}
			else if (key_word == "WRITE") 
			{
				write_cmd();
				t = ts.get();
			}
			else if (key_word == "OPEN") 
			{
				open_cmd();
				t = ts.get();
			}
			else if (key_word == "INSERTINTO") 
			{
				insert_cmd();
				t = ts.get();
			}
			break;

		case '9':
			ts.putback(t);
			new_view = relation_name();
			t = ts.get();
			break;

		case '<':
			t = ts.get();
			if (t.kind == '-') 
			{
				operation_or_name = identifier();
				if (operation_or_name == "select") 
				{
					query_view = selection_qry();
					query_view.set_name(new_view);
					db_ptr.add_table(query_view);
				}
				else if (operation_or_name == "project") 
				{
					query_view = projection_qry();
					query_view.set_name(new_view);
					db_ptr.add_table(query_view);
				}
				else if (operation_or_name == "rename") 
				{
					query_view = renaming_qry();
					query_view.set_name(new_view);
					db_ptr.add_table(query_view);
				}
				else  //first token will be a table name or atomic expr
				{
					ts.get();
				
					//put operation_or_name back on the front of cin buffer
					for (int i = 0; i < operation_or_name.size() + 2; i++) 
					{
						cin.unget();
					}					
					query_view = tables_qry();
					query_view.set_name(new_view);
					db_ptr.add_table(query_view);
				}
			}
			break;

		case '0':
			keep_going = 0;
			break;

		default:
			t = ts.get();
			break;
		}
	}			
}