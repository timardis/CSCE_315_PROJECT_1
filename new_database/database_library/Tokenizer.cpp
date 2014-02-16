#include "Tokenizer.h"


Tokenizer::Tokenizer()
{
  currentIndex = -1;
}

void Tokenizer::tokenizeInput(string input)
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
				insertToken(s_for_token);
				s_for_token.clear();
			}
			switch (_input[index]){
			case '(':
				insertToken("(");
				break;
			case ')':
				insertToken(")");
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
				insertToken(s_for_token);
				s_for_token.clear();
				break;
			case '+':
				insertToken("+");
				break;
			case '-':
				insertToken("-");
				break;
			case '*':
				insertToken("*");
				break;
			case ',':
				insertToken(",");
				break;
			case ';':
				insertToken(";");
				break;
			case '=':
				s_for_token = "=";
				if (_input[index + 1] == '='){
					s_for_token += "=";
					index++;
				}
				insertToken(s_for_token);
				s_for_token.clear();
				break;
			case '|':
				s_for_token = "|";
				if (_input[index + 1] == '|'){
					s_for_token += "|";
					index++;
				}
				if (s_for_token == "||"){
					insertToken(s_for_token);
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
					insertToken(s_for_token);
					s_for_token.clear();
				}
				else{
					throw runtime_error("Invalid char after '&'");
				}
				break;
			case '"':
				insertToken("\"");
				break;

			case '\n': case '\r':
				break;
			default:
				break;
			}

		}

	}
}

void Tokenizer::reinitialize()
{

}

string Tokenizer::peek()
{
  if(remainingTokens() > 0)
  {
    string s = tokens[currentIndex];
    return s;
  }
}
  
string Tokenizer::pop()
{
  if(remainingTokens() > 0)
  {
    string s = tokens[currentIndex];
    currentIndex++;
    return s;
  }
  else
  {
    throw runtime_error("No token available");
  }
}

int Tokenizer::remainingTokens()
{
  return tokens.size();
}

void Tokenizer::insertToken(string _token)
{
  tokens.push_back(_token);
  currentIndex = 0;
}

