#ifndef PARSER_H
#define PARSER_H

#include "Database.h"
#include <iostream>
#include <string>
#include <regex>

using namespace std;

enum Expression
{
  ATOMIC_EXPR, SELECT, PROJECT, RENAME, 
  UNION, DIFFERENCE, PRODUCT, NATURAL_JOIN
};

enum Command { 
  OPEN, CLOSE, WRITE, EXIT, SHOW, 
  CREATE, UPDATE, INSERT, DELETE, QUERY
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
  void processInput(string _input);
  void getToken(string& _input);
  Command getCommand(string _input);
  
  void processQuery(string _input);
};
#endif
