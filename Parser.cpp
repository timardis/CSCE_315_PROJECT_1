#include "Parser.h"

Parser::Parser() {}
void Parser::tokenize_input(string input)
{
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
				token_vec.push_back(s_for_token);
				s_for_token.clear();
			}
			switch (_input[index]){
			case '(':
				token_vec.push_back("(");
				break;
			case ')':
				token_vec.push_back(")");
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
				token_vec.push_back(s_for_token);
				s_for_token.clear();
				break;
			case '+':
				token_vec.push_back("+");
				break;
			case '-':
				token_vec.push_back("-");
				break;
			case '*':
				token_vec.push_back("*");
				break;
			case ',':
				token_vec.push_back(",");
				break;
			case ';':
				token_vec.push_back(";");
				break;
			case '=':
				s_for_token = "=";
				if (_input[index + 1] == '='){
					s_for_token += "=";
					index++;
				}
				token_vec.push_back(s_for_token);
				s_for_token.clear();
				break;
			case '|':
				s_for_token = "|";
				if (_input[index + 1] == '|'){
					s_for_token += "|";
					index++;
				}
				if (s_for_token == "||"){
					token_vec.push_back(s_for_token);
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
					token_vec.push_back(s_for_token);
					s_for_token.clear();
				}
				else{
					throw runtime_error("Invalid char after '&'");
				}
				break;
			case '"':
				token_vec.push_back("\"");
				break;
			
			case '\n': case '\r':
				break;
			default:
				break;
			}
			
		}

	}
	for (int i = 0; i < token_vec.size(); i++){
		cout << token_vec[i] << endl;
	}
}


