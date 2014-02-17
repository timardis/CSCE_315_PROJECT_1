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

  Tuple(vector<Type>& _types, vector<string>& _attr_names, vector<string>& _values)
  {
    // check for size compatability
    if(_types.size() == _values.size())
    {
      size = _types.size();
      types = _types;
      attr_names = _attr_names;
      values = _values;
    }
    else
    {
      // size incompatible, throw Exception
      throw runtime_error("Different vector sizes");
    }
  }
  
  int getSize()
  {
    return size;
  }
  vector<Type>& get_types()
  {
    return types;
  }
  vector<string>& get_values()
  {
    return values;
  };
  vector<string>& get_attr_names()
  {
    return attr_names;
  }
};

#endif