#include "Parser.h"

Parser::Parser() {}

void Parser::processInput(string _input)
{
  try
  {
    InputType type = getInputType(_input);
    switch(type)
    {
    case QUERY:
      processQuery(_input);
      break;
    default:
      processCommand(type);
      break;
    }
  }
  catch(exception& e)
  {
    cout << "Exception: " << e.what() << endl;
  }
}

void Parser::processQuery(string _input)
{
  string input = _input;
  string relation_name;
  smatch m;

  // query ::= relation-name <- expr;
  if (regex_search(input, m, regex("^[[:blank:]]*([a-zA-Z1-9]+)[[:blank:]]*<-[[:blank:]]*")))
  {
    // Extract relation-name from input string
    relation_name = m[1].str();

    // Strip off 'relation-name <-' and any spaces after
    input = m.suffix.str();

    // DEBUG
    cout << input << endl;
  }
  else
  {
    throw runtime_error("Invalid Input");
  }

  Table t = expression(input);
}

void Parser::processCommand(InputType _inType)
{

}

Table Parser::expression(string _input)
{

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