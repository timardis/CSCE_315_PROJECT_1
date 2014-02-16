#include "Parser.h"

Parser::Parser() {}

void Parser::processInput(string _input)
{
  try
  {
    // Tokenize the input, divide the string input into minimal units
    tokenizer.tokenizeInput(_input);
    
    string token;

    // Check if there is any token
    if(tokenizer.remainingTokens() > 0)
    {
      token = tokenizer.peek();
    }
    else
    {
      // Most likely blank line, return
      return;
    }

    InputType type = getInputType(token);
    switch(type)
    {
    case QUERY:
      processQuery();
      break;
    default:
      processCommand();
      break;
    }
  }
  catch(exception& e)
  {
    cout << "Exception: " << e.what() << endl;
  }
}

void Parser::processQuery()
{
  //
  string relation_name = tokenizer.pop();

  // query ::= relation-name <- expr;
  string t1 = tokenizer.pop();
  string t2 = tokenizer.pop();

  if (t1 == "<")
  {

  }
  else
  {
    throw runtime_error("Invalid Input");
  }

  //Table t = expression(input);
}

void Parser::processCommand()
{

}

Table Parser::expression(string _input)
{
  // Dummy code to compile
  Table* t = NULL;
  return *t;
}

InputType Parser::getInputType(string _input)
{
  smatch m;
  if (regex_search(_input, m, regex("^[[:blank:]]*([a-zA-Z1-9]+)[[:blank:]]*")))
  {
    string op = m[1].str();

    if(op == string("OPEN"))
    {
      return OPEN;
    }
    else if(op == string("CLOSE"))
    {
      return CLOSE;
    }
    else if(op == string("WRITE"))
    {
      return WRITE;
    }
    else if(op == string("EXIT"))
    {
      return EXIT;
    }
    else if(op == string("SHOW"))
    {
      return SHOW;
    }
    else if(op == string("CREATE"))
    {
      return CREATE;
    }
    else if(op == string("UPDATE"))
    {
      return UPDATE;
    }
    else if(op == string("INSERT"))
    {
      return INSERT;
    }
    else if(op == string("DELETE"))
    {
      return DELETE;
    }
    else
    {
      return QUERY;
    }
  }
  else
  {
    throw runtime_error("Invalid Input");
  }
}
