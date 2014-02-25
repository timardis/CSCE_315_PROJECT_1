#ifndef TUPLE_H
#define TUPLE_H

using namespace std;

#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <regex>

enum Type { INTEGER, VARCHAR };

class Tuple
{
public:
  int size;
  vector<Type> types;
  vector<string> attr_names;
  //  store everything as strings for now
  vector<string> values;

  Tuple(vector<Type>& _types, vector<string>& _attr_names, vector<string>& _values);
  int getSize();
  vector<Type>& get_types();
  vector<string>& get_values();
  vector<string>& get_attr_names();
};

#endif