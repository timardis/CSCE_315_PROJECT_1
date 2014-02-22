#include "Database.h"
#include "Parser.h"

#include <iostream> 
  
using namespace std; 
  
int main(){ 
  
        Parser p;
		string line;
		fstream f;
		f.open("input.txt");
		while(getline(f, line))
			p.process_input(line);
		int i;
       cin >> i; 
      
}