#include "Tuple.h"

Tuple:: Tuple(vector<Type>& _types, vector<string>& _attr_names, vector<string>& _values)
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

 int Tuple::getSize()
  {
    return size;
  }

 vector<Type>& Tuple::get_types()
  {
    return types;
  }

  vector<string>& Tuple::get_values()
  {
    return values;
  }

   vector<string>& Tuple::get_attr_names()
  {
    return attr_names;
  }