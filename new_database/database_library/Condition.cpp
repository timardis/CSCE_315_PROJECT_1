#include "Condition.h"

Comparison::Comparison(Tokenizer& tokenizer)
{
  main_condition = NULL;
  if(tokenizer.peek() == "(")
  {
    main_condition = new Condition(tokenizer);
  }
  else
  {
    attr_name = tokenizer.pop();
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
    if(tokenizer.peek() == "\"")
    {
      tokenizer.pop();        // pop the first double quote
      rhs = tokenizer.pop();
      if(tokenizer.peek() != "\"")
      {
        throw runtime_error("Missing closing double quote after string input");
      }
      tokenizer.pop();        // pop the second double quote
    }
    else
    {
      rhs = tokenizer.pop();
    }
  }
}

bool Comparison::evaluate_tuple(Tuple& tup)
{
  if(main_condition != NULL)
  {
    return main_condition->evaluate_tuple(tup);
  }

  // evaluate the comparison
  else
  {
    for(int i = 0; i < tup.getSize(); i++)
    {
      
      // check for the attribute to be evaluated
      if(tup.get_attr_names()[i] == attr_name)
      {
        Type t = tup.get_types()[i];
        string lhs = tup.get_values()[i];
        if(t == INTEGER)
        {
          // convert strings to ints
          int lhs_int = stoi(lhs);
          int rhs_int = stoi(rhs);

          switch(op)
          {
          case GREATER:
            return lhs_int > rhs_int;
            break;
          case GREATER_EQUAL:
            return lhs_int >= rhs_int;
            break;
          case EQUAL:
            return lhs_int == rhs_int;
            break;
          case NOT_EQUAL:
            return lhs_int != rhs_int;
            break;
          case LESS:
            return lhs_int < rhs_int;
            break;
          case LESS_EQUAL:
            return lhs_int <= rhs_int;
            break;
          default:
            throw runtime_error("Unknown Comparison Operator Input");
            break;
          }
        }
        else if(t == VARCHAR)
        {
          switch(op)
          {
          case GREATER:
            return lhs > rhs;
            break;
          case GREATER_EQUAL:
            return lhs >= rhs;
            break;
          case EQUAL:
            return lhs == rhs;
            break;
          case NOT_EQUAL:
            return lhs != rhs;
            break;
          case LESS:
            return lhs < rhs;
            break;
          case LESS_EQUAL:
            return lhs <= rhs;
            break;
          default:
            throw runtime_error("Unknown Comparison Operator Input");
            break;
          }
        }
        else
          throw runtime_error("Unknown Attribute Type");
        break;
      }
    }
  }
}
/******************************************************************/
Comparison::~Comparison()
{
  if(main_condition != NULL)
  {
	  delete main_condition;
     main_condition = NULL;
  }
}

Conjunction::Conjunction(Tokenizer& tokenizer)
{
  main_comparison = NULL;
  optional_comparison = NULL;
  has_optional_comparison = false;

  main_comparison = new Comparison(tokenizer);
  if(tokenizer.peek() == "&&")
  {
    tokenizer.pop();  // pop the || token
    optional_comparison = new Comparison(tokenizer);
    has_optional_comparison = true;
  }
}

bool Conjunction::evaluate_tuple(Tuple& tup)
{
  if(!has_optional_comparison)
  {
    // has only one comparison
    bool main_comp = main_comparison->evaluate_tuple(tup);
    return main_comp;
  }
  else
  {
    // has two comparisons
    bool main_comp = main_comparison->evaluate_tuple(tup);
    bool optional_comp = optional_comparison->evaluate_tuple(tup);
    return main_comp && optional_comp;
  }
}

Conjunction::~Conjunction()
{
  if(main_comparison != NULL)
  {
    delete main_comparison;
    main_comparison = NULL;
  }
  if(optional_comparison != NULL)
  {
    delete optional_comparison;
    optional_comparison = NULL;
  }
}

Condition::Condition(Tokenizer& tokenizer)
{
  main_conjunction = NULL;
  optional_conjunction = NULL;

  try{
    has_optional_conjunction = false;
    if(tokenizer.pop() != "(")
    {
      throw runtime_error("Invalid condition input. No '('");
    }

    main_conjunction = new Conjunction(tokenizer);
    if(tokenizer.peek() == "||")
    {
      tokenizer.pop();  // pop the || token
      optional_conjunction = new Conjunction(tokenizer);
      has_optional_conjunction = true;
    }

    // check for ending parenthesis
    if(tokenizer.pop() != ")")
    {
      throw runtime_error("Invalid condition input. No ')'");
    }
  }
  catch(exception& e)
  {
    cout << "Exception: " << e.what() << endl;
  }
}

bool Condition::evaluate_tuple(Tuple& tup)
{
  if(!has_optional_conjunction)
  {
    // there was only one conjunction
    bool main_conj = main_conjunction->evaluate_tuple(tup); 
    return main_conj;
  }
  else
  {
    // there are to conjunctions
    bool main_conj = main_conjunction->evaluate_tuple(tup);
    bool optional_conj = optional_conjunction->evaluate_tuple(tup);
    return main_conj || optional_conj;
  }
}

Condition::~Condition()
{
  if(main_conjunction != NULL)
  {
    delete main_conjunction;
    main_conjunction = NULL;
  }
  if(optional_conjunction != NULL)
  {
    delete optional_conjunction;
    optional_conjunction = NULL;
  }
}