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

class Comparison
{
public:
  Comparison() {};
  Comparison(Tokenizer& tokenizer);
  string lhs;         // name of attribute to be compared
  Comp_Operator op;   
  string rhs;         // value to be compared against

  bool evaluate_tuple(Tuple tup);
};

class Conjunction
{
public:
  Conjunction() {};
  Conjunction(Tokenizer& tokenizer);
  Comparison main_comparison;
  Comparison optional_comparison;

  bool evaluate_tuple(Tuple tup);
};
class Condition
{
public:
  Condition() {};
  Condition(Tokenizer& tokenizer);
  Conjunction main_conjunction;
  Conjunction optional_conjunction;

  bool evaluate_tuple(Tuple tup);
};


#endif
