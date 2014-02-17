#ifndef PARSER_H
#define PARSER_H

#include "Database.h"
#include "Tokenizer.h"
#include <iostream>
#include <string>
#include <regex>
#include <fstream>

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


class Parser
{
private:
  Database db;

    int view_num;
  Tokenizer tokenizer;
  // 'Bridge' functions for the Tokenizer
  //string pop() {return tokenizer.pop();}
  //string peek() {return tokenizer.peek();}
  //void tokenizeInput(string _input) {tokenizer.tokenizeInput(_input);}

public:
  Parser();


  void processInput(string _input);
  InputType getInputType(string _input);
  ExpressionType getExpressionType(string _input);
  void processQuery();
  void processCommand(InputType t);
  void open(string relation_name);
  void close(string relation_name);
  void exit();
  void show(string table_name);
  
  // Command functions
  void createTable();
  void insert_into();

  //Query functions
  string selection();
  string projection();
  string rename();
  string set_union_parser(string left_atom_expr);
  string set_difference_parser(string left_atom_expr);
  string cross_product_parser(string left_atom_expr);
  string set_natural_join(string left_atom_expr);

  //helper functions
  pair<vector<string>, vector<string>> get_typed_attribute_list();
  vector<string> get_keys();
  string get_attribute_type();
  string expression();
  string atomic_expression();
  string get_dummy_view_name();
  vector<string> get_attribute_list();


};
#endif
