#include "Condition.h"

Comparison::Comparison(Tokenizer& tokenizer)
{
  is_condition = false;
  if(tokenizer.peek() == "(")
  {
    main_condition = Condition(tokenizer);
    is_condition = true;
  }
  else
  {
    lhs = tokenizer.pop();
    string op_tok = tokenizer.pop();
    if(op_tok == ">")
      op = GREATER;
    else if(op_tok == ">=")
      op = GREATER_EQUAL;
    else if(op_tok == "==")
      op = EQUAL;
    else if(op_tok == "!=")
      op = NOT_EQUAL;
    else if(op_tok == "<")
      op = LESS;
    else if(op_tok == "<=")
      op = LESS_EQUAL;
    else
      throw runtime_error("Invalid Comparison Operator Input");
    rhs = tokenizer.pop();
  }
}

bool Comparison::evaluate_tuple(Tuple& tup)
{

}

Conjunction::Conjunction(Tokenizer& tokenizer)
{
  has_optional_comparison = false;

  main_comparison = Comparison(tokenizer);
  if(tokenizer.peek() == "&&")
  {
    tokenizer.pop();  // pop the || token
    optional_comparison = Comparison(tokenizer);
    has_optional_comparison = true;
  }
}

bool Conjunction::evaluate_tuple(Tuple& tup)
{

}

Condition::Condition(Tokenizer& tokenizer)
{
  has_optional_conjunction = false;
  if(tokenizer.pop() != "(")
  {
    throw runtime_error("Invalid condition input. No '('");
  }

  main_conjunction = Conjunction(tokenizer);
  if(tokenizer.peek() == "||")
  {
    tokenizer.pop();  // pop the || token
    optional_conjunction = Conjunction(tokenizer);
    has_optional_conjunction = true;
  }

  // check for ending parenthesis
  if(tokenizer.pop() != ")")
  {
    throw runtime_error("Invalid condition input. No ')'");
  }
}

bool Condition::evaluate_tuple(Tuple& tup)
{

}
