#include "Database.h"
#include "Parser.h"

#include <iostream> 
  
using namespace std; 
  
int main(){ 
        Database db; 
  
        string title = "Relation 1"; 
        vector<string> keys; 
        vector<string> attributes; 
        vector<string> attribute_types; 
        vector<string> tuple1; 
        vector<string> tuple2; 
        vector<string> tuple3; 
        vector<string> tuple4; 
  
        attributes.push_back("Attribute 1"); 
        attributes.push_back("Attribute 2"); 
        attributes.push_back("Attribute 3"); 
        attributes.push_back("Attribute 4"); 
  
        attribute_types.push_back("CHAR(10)"); 
        attribute_types.push_back("INT"); 
        attribute_types.push_back("DATE"); 
        attribute_types.push_back("FLOAT"); 
  
        keys.push_back("Attribute 1"); 
        keys.push_back("Attribute 3"); 
  
        tuple1.push_back("Allison"); 
        tuple1.push_back("1"); 
        tuple1.push_back("2013-10-10"); 
        tuple1.push_back("12.38"); 
  
        tuple2.push_back("Bill"); 
        tuple2.push_back("2"); 
        tuple2.push_back("2010-08-01"); 
        tuple2.push_back("48.2"); 
  
        tuple3.push_back("Charlotte"); 
        tuple3.push_back("3"); 
        tuple3.push_back("2033-08-08"); 
        tuple3.push_back("65.54"); 
  
        tuple4.push_back("Doug"); 
        tuple4.push_back("4"); 
        tuple4.push_back("2004-06-13"); 
        tuple4.push_back("89.38"); 
  
        cout << "TEST CREATE(), INSERT_TUPLE(), SHOW(): create and show a table\n"; 
        db.create(title, attributes, attribute_types, keys); 
        db.insert_tuple(title, tuple1); 
        db.insert_tuple(title, tuple2); 
        db.insert_tuple(title, tuple3); 
        db.insert_tuple(title, tuple4); 
        db.show(title); 
        cout << "\n\n"; 
      
        vector<string> tuple5; 
        vector<string> tuple6; 
        vector<string> tuple7; 
        vector<string> tuple8; 
      
        tuple5.push_back("Jake"); 
        tuple5.push_back("57"); 
        tuple5.push_back("1991-10-18"); 
        tuple5.push_back("54.32"); 
  
        tuple6.push_back("Joe"); 
        tuple6.push_back("10"); 
        tuple6.push_back("2015-01-05"); 
        tuple6.push_back("85.3"); 
  
        tuple7.push_back("Charlotte"); 
        tuple7.push_back("3"); 
        tuple7.push_back("2033-08-08"); 
        tuple7.push_back("65.54"); 
  
        tuple8.push_back("Doug"); 
        tuple8.push_back("4"); 
        tuple8.push_back("2004-06-13"); 
        tuple8.push_back("89.38"); 
  
        db.create("Relation 2", attributes, attribute_types, keys); 
        db.insert_tuple("Relation 2", tuple5); 
        db.insert_tuple("Relation 2", tuple6); 
        db.insert_tuple("Relation 2", tuple7); 
        db.insert_tuple("Relation 2", tuple8); 
        db.show("Relation 2"); 
        cout << "\n\n\n\n"; 
      
        cout << "TEST REMOVE(): remove row 4 of relation 1\n"; 
        db.remove(title, 0); 
        db.show(title); 
        cout << "\n\n"; 
      
        cout << "TEST UPDATE(): change Attribute 2 on row 3 of relation 1 to '55'\n"; 
        vector<string> attribute; 
        attribute.push_back("Attribute 2"); 
        vector<string> data; 
        data.push_back("55"); 
        db.update(title, attribute, data, 0); 
        db.show(title); 
        cout << "\n\n"; 
  
          
        cout << "TEST SELECT(): select row 3 and row 5 of relation 1\n"; 
        //db.select("view1", title, 0); 
        //db.select("view1", title, 2); 
        //db.show("view1"); 
        cout << "\n\n"; 
      
        cout << "TEST PROJECT(): project the Attribute 2 column\n"; 
        attribute.push_back("Attribute 1"); 
        db.project("view2", title, attribute); 
        db.show("view2"); 
        cout << "\n\n"; 
      
        cout<< "TEST RENAME(): \n"; 
        attributes[0] = "Attribute 5"; 
        attributes[1] = "Attribute 6"; 
        attributes[2] = "Attribute 7"; 
        attributes[3] = "Attribute 8"; 
        db.rename("view3", title, attributes); 
        db.show("view3"); 
        cout << "\n\n"; 
  
        cout << "TEST SET_UNION(): relation 1 in union with relation 2\n"; 
        db.set_union("view4", title, "Relation 2"); 
        db.show("view4"); 
        cout << "\n\n"; 
        int i; 
  
        cout << "TEST SET_DIFFERENCE(): relation 1 - relation 2 \n"; 
        db.set_difference("view5", title, "Relation 2"); 
        db.show("view5"); 
        cout<<"\n\n"; 
  
        cout << "TEST CROSS_PRODUCT(): relation 1 X relation 2\n"; 
        db.cross_product("view6", title, "Relation 2"); 
        db.show("view6"); 
        cout<<"\n\n"; 
  
        cout << "TEST INSERT_VIEW(): insert view1 into relation 1\n"; 
        //db.insert_view("Relation 2", "view1"); 
        db.show("Relation 2"); 
        cout << "\n\n"; 
  
        db.remove_table("Relation 1"); 
  
        string table_name1 = "Employee table"; 
        vector<string> attribute_name; 
        vector<string>attribute_t1; 
        vector<string> key_1; 
        vector<string>tuple1_1; 
        vector<string>tuple1_2; 
        vector<string>tuple1_3; 
        vector<string>tuple1_4; 
        vector<string>tuple1_5; 
        vector<string>tuple1_6; 
  
        attribute_name.push_back("LastName"); 
        attribute_name.push_back("Department ID"); 
        attribute_t1.push_back("string"); 
        attribute_t1.push_back("int"); 
        key_1.push_back("LastName"); 
        tuple1_1.push_back("Rafferty"); 
        tuple1_1.push_back("31"); 
        tuple1_2.push_back("Jones"); 
        tuple1_2.push_back("33"); 
        tuple1_3.push_back("Heisenberg"); 
        tuple1_3.push_back("33"); 
        tuple1_4.push_back("Robinson"); 
        tuple1_4.push_back("34"); 
        tuple1_5.push_back("Smith"); 
        tuple1_5.push_back("34"); 
        tuple1_6.push_back("John"); 
        tuple1_6.push_back("NULL"); 
        db.create(table_name1, attribute_name, attribute_t1, key_1); 
        db.insert_tuple(table_name1, tuple1_1); 
        db.insert_tuple(table_name1, tuple1_2); 
        db.insert_tuple(table_name1, tuple1_3); 
        db.insert_tuple(table_name1, tuple1_4); 
        db.insert_tuple(table_name1, tuple1_5); 
        db.insert_tuple(table_name1, tuple1_6); 
        db.show(table_name1); 
        cout << "\n"; 
        string table_name2 = "Departmnet table"; 
        vector<string> attribute2_name; 
        vector<string>attribute_t2; 
        vector<string> key_2; 
        vector<string>tuple2_1; 
        vector<string>tuple2_2; 
        vector<string>tuple2_3; 
        vector<string>tuple2_4; 
        attribute2_name.push_back("Department ID"); 
        attribute2_name.push_back("Department Name"); 
        key_2.push_back("Department ID"); 
        attribute_t2.push_back("int"); 
        attribute_t2.push_back("string"); 
        tuple2_1.push_back("31"); 
        tuple2_1.push_back("Sales"); 
        tuple2_2.push_back("33"); 
        tuple2_2.push_back("Engineering"); 
        tuple2_3.push_back("34"); 
        tuple2_3.push_back("Chemical"); 
        tuple2_4.push_back("35"); 
        tuple2_4.push_back("Marketing"); 
        db.create(table_name2, attribute2_name, attribute_t2, key_2); 
        db.insert_tuple(table_name2, tuple2_1); 
        db.insert_tuple(table_name2, tuple2_2); 
        db.insert_tuple(table_name2, tuple2_3); 
        db.insert_tuple(table_name2, tuple2_4); 
  
        db.show(table_name2); 
  
        db.join("join", table_name1, table_name2); 
        db.show("join"); 
  
        Parser p;
        p.processInput(string(" CREATE TABLE select <-  (kind == \"dogs\") "));

        
        Tokenizer tok;
        tok.tokenizeInput("(age < 10)");
			  Condition c(tok);

			  vector<Type> typeVec;
			  typeVec.push_back(INTEGER);
			  typeVec.push_back(VARCHAR);

			  vector<string> attrVec;
			  attrVec.push_back("age");
			  attrVec.push_back("name");

			  vector<string> valVec;
			  valVec.push_back("9");
			  valVec.push_back("Bob");

			  Tuple tup(typeVec, attrVec, valVec);

			  bool test = c.evaluate_tuple(tup);
        
        cin >> i; 
      
}