#include "Tokenizer.h"


Tokenizer::Tokenizer()
{
  current_index = -1;
}

void Tokenizer::tokenize_input(string input)
{
	tokens.clear();
  reinitialize();

  stringstream line_stream(input);
	string _input;
	while (line_stream >> _input){
		//char[] input = _input.c_str();
		string s_for_token = "";

		int input_length = _input.size();

		for (int index = 0; index < input_length; index++){
			char ch = _input[index];
			//putting stuff with alpha or digit or _ in one token
			while (isalpha(ch) || isdigit(ch) || ch == '_'){
				s_for_token += ch;
				index++;
				ch = _input[index];	
			}
			if (s_for_token != ""){
				insert_token(s_for_token);
				s_for_token.clear();
			}
			switch (_input[index]){
			case '(':
				insert_token("(");
				break;
			case ')':
				insert_token(")");
				break;
			case '<':
				s_for_token = "<";
				if (_input[index + 1] == '='){
					s_for_token += "=";
					index++;
				}
				else if (_input[index + 1] == '-'){
					s_for_token += "-";
					index++;
				}
				insert_token(s_for_token);
				s_for_token.clear();
				break;
			case '>':
				s_for_token = ">";
				if (_input[index + 1] == '='){
					s_for_token += "=";
					index++;
				}
				insert_token(s_for_token);
				s_for_token.clear();
				break;
			case '+':
				insert_token("+");
				break;
			case '-':
				insert_token("-");
				break;
			case '*':
				insert_token("*");
				break;
			case ',':
				insert_token(",");
				break;
			case ';':
				insert_token(";");
				break;
			case '=':
				s_for_token = "=";
				if (_input[index + 1] == '='){
					s_for_token += "=";
					index++;
				}
				insert_token(s_for_token);
				s_for_token.clear();
				break;
			case '|':
				s_for_token = "|";
				if (_input[index + 1] == '|'){
					s_for_token += "|";
					index++;
				}
				if (s_for_token == "||"){
					insert_token(s_for_token);
					s_for_token.clear();
				}
				else{
					throw runtime_error("Invalid char after '|'");
				}
				break;
			case '&':
				s_for_token = "&";
				if (_input[index + 1] == '&'){
					s_for_token += "&";
					index++;
				}
				if (s_for_token == "&&"){
					insert_token(s_for_token);
					s_for_token.clear();
				}
				else{
					throw runtime_error("Invalid char after '&'");
				}
				break;
			case '"':
				insert_token("\"");
				break;

			case '\n': case '\r':
				break;
			default:
				break;
			}

		}

	}
	for (int i = 0; i < tokens.size(); i++){
		cout << tokens[i] << endl;
	}
}

void Tokenizer::reinitialize()
{
  tokens.clear();
  currentIndex = -1;
}

string Tokenizer::peek()
{
  if(remaining_tokens() > 0)
  {
    string s = tokens[current_index];
    return s;
  }
}
  
string Tokenizer::pop()
{
  if(remaining_tokens() > 0)
  {
    string s = tokens[current_index];
    current_index++;
    return s;
  }
  else
  {
    throw runtime_error("No token available");
  }
}

int Tokenizer::remaining_tokens()
{
  return tokens.size();
}

void Tokenizer::insert_token(string _token)
{
  tokens.push_back(_token);
  current_index = 0;
}

string Tokenizer:: get_previous_data(){
	return tokens[current_index-1];
}

