#include "Parser.h"

Parser::Parser() {}

void Parser::processInput(string _input)
{
  //string input = 
  InputType c = getInputType(_input);
  switch(c)
  {
  case QUERY:
    processQuery(_input);
    break;
  default:
    processCommand(c);
    break;
  }
}

void Parser::processQuery(string _input)
{
  smatch m;
  if (regex_search(_input, m, regex("^[[:blank:]]*([a-zA-Z1-9]+)[[:blank:]]+")))
  {

  }
}

void Parser::processCommand(InputType _inType)
{

}

void Parser::getToken(string& _input)
{
  
}

InputType Parser::getInputType(string _input)
{
  smatch m;
  if (regex_search(_input, m, regex("^[[:blank:]]*([a-zA-Z1-9]+)[[:blank:]]+")))
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
    throw runtime_error("Invalid input");
  }
}