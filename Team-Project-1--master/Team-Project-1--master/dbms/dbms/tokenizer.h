#ifndef TOKENIZER_H
#define TOKENIZER_H


#include "parser.h"
class Token {
public:
	char kind;        // what kind of token
	int value;     // for numbers: a value 
	char letter;
	Token(char ch)    // make a character Token from a char
		:kind(ch), value(0), letter('\0') { }
	Token(char ch, char ch2)	// make a letter Token from a char and a letter
		:kind(ch), value(0), letter(ch2){ }
	Token(char ch, int val)   // make a number Token from a char and a double
		:kind(ch), value(val), letter('\0') { }

};

class Token_stream {
public:
	Token_stream();   // make a Token_stream that reads from cin
	Token get();      // get a Token (get() is defined elsewhere)
	void putback(Token t);    // put a Token back

private:
	bool full;        // is there a Token in the buffer?
	Token buffer;     // here is where we keep a Token put back using putback()
};

#endif