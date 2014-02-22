#ifndef PARSER_H
#define PARSER_H

#include "Database.h"
//#include "Tokenizer.h"
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

public:
  Parser();


  void process_input(string _input);
  InputType get_input_type(string _input);
  ExpressionType get_expression_type(string _input);
  void process_query();
  void process_command(InputType t);
  void open();
  void close();
  void exit();
  void show();
  void write();
  void delete_from();
  void update_to();
  
  // Command functions
  void create_table();
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
  pair<vector<string>, vector<string>> get_attr_for_update();


};
#endif
