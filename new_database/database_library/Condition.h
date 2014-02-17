#ifndef CONDITION_H
#define CONDITION_H

#include "Tuple.h"
#include "Tokenizer.h"
#include <string>

enum Comp_Operator{
  GREATER, GREATER_EQUAL,
  EQUAL, NOT_EQUAL,
  LESS, LESS_EQUAL
};

class Condition;

class Comparison
{
  bool is_condition;
  Condition* main_condition;
  string attr_name;         // name of attribute to be compared
  Comp_Operator op;
  string rhs;
public:
  Comparison() {};
  Comparison(Tokenizer& tokenizer);       // value to be compared against
  ~Comparison();
  bool evaluate_tuple(Tuple& tup);
};

class Conjunction
{
  bool has_optional_comparison;
  Comparison main_comparison;
  Comparison optional_comparison;
public:
  Conjunction() {};
  Conjunction(Tokenizer& tokenizer);

  bool evaluate_tuple(Tuple& tup);
};

class Condition
{
  bool has_optional_conjunction;
  Conjunction main_conjunction;
  Conjunction optional_conjunction;
public:
  Condition() {};
  Condition(Tokenizer& tokenizer);

  bool evaluate_tuple(Tuple& tup);
};

#endif
