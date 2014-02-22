#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <regex>

using namespace std;

class Tokenizer
{
private:
  vector<string> tokens;
  int current_index;

  void insert_token(string _token);

public:
  Tokenizer();
  void tokenize_input(string _input);

  // clear token vector and reset current index for next input string
  void reinitialize();
  
  // return the next token without taking it off the queue
  string peek();

  // return the next token and take it off the queue
  string pop();

  // return number of remaining tokens
  int remaining_tokens();

  void add_bracket();

  string get_previous_data();
};