#ifndef PARSER_H
#define PARSER_H

#include "Database.h"
#include <iostream>
#include <string>
#include <regex>

using namespace std;

enum ExpressionType
{
  ATOMIC_EXPR, SELECT, PROJECT, RENAME, 
  UNION, DIFFERENCE, PRODUCT, NATURAL_JOIN
};

enum InputType
{
  // Commands
  OPEN, CLOSE, WRITE, EXIT, SHOW, 
  CREATE, UPDATE, INSERT, DELETE,
  
  // Query
  QUERY
};

class Token
{
public:
  string str_value;
};

class Parser
{
private:
  Database db;
  vector<Token> token_vec;

public:
  Parser();

  Table expression(string _input);

  void processInput(string _input);
  InputType getInputType(string _input);
  
  void processQuery(string _input);
  void processCommand(InputType _inType);
};
#endif
